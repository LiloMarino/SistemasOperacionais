import matplotlib.pyplot as plt
from matplotlib.ticker import MultipleLocator

# Definição da classe Processo
class Processo:
    def __init__(self, nome, execucao, ativacao, io_events):
        self.nome = nome
        self.execucao = execucao  # Tempo total de execução
        self.ativacao = ativacao  # Tempo em que o processo é ativado
        self.io_events = io_events  # Lista de eventos de I/O (tuples com tempo de início e duração)
        self.execucao_restante = execucao  # Tempo restante de execução
        self.timeline = []  # Lista para armazenar a timeline do processo

    def processar_io(self, start_time, i):
        """
        Processa os eventos de I/O de um processo.
        :param start_time: Tempo de início da execução ou I/O
        :param i: Índice do próximo evento de I/O
        :return: Lista de eventos de I/O para a timeline, novo start_time, índice de I/O incrementado
        """
        if i < len(self.io_events) and self.io_events[i][0] <= (start_time - self.ativacao):
            io_start = start_time
            io_end = io_start + self.io_events[i][1]
            # Adiciona o evento de I/O à timeline do processo
            self.timeline.append(("I/O", io_start, io_end))
            return io_end, i + 1
        return start_time, i

    def processar_execucao(self, start_time, exec_time, i):
        """
        Processa a execução de um processo até o próximo evento de I/O ou término.
        :param start_time: Tempo de início da execução
        :param exec_time: Tempo de execução que o processo pode realizar
        :param i: Índice do próximo evento de I/O
        :return: Lista de eventos de Execução para a timeline, novo start_time, tempo restante de execução, novo índice de I/O
        """
        if i < len(self.io_events):
            exec_time = min(self.io_events[i][0], exec_time)  # Tempo até o próximo I/O
        end_time = start_time + exec_time
        self.execucao_restante -= exec_time
        # Adiciona o evento de Execução à timeline do processo
        self.timeline.append(("Execução", start_time, end_time))
        return end_time, i


# Definição da classe Escalonador
class Escalonador:
    def __init__(self, processos, quantum):
        self.processos = processos  # Lista de processos
        self.tempo_atual = 0  # Tempo atual do escalonador
        self.turnarounds = {}  # Dicionário para armazenar os turnarounds dos processos
        self.quantum = quantum  # Quantum para o escalonamento Round-Robin

    def escalonar(self):
        """
        Realiza o escalonamento Round-Robin com I/O, retornando a timeline de todos os processos.
        :return: Timeline de processos e turnarounds
        """
        fila = self.processos.copy()  # Fila de processos a serem executados
        while fila:
            proc = fila.pop(0)
            start_time = max(self.tempo_atual, proc.ativacao)
            i = 0
            exec_time = min(self.quantum, proc.execucao_restante)  # Tempo de execução até o quantum

            # Processar execução do processo
            start_time, i = proc.processar_execucao(start_time, exec_time, i)
            # Processar I/O do processo, se houver
            start_time, i = proc.processar_io(start_time, i)

            # Se o processo não terminou e não entrou em I/O, re-adiciona na fila
            if proc.execucao_restante > 0 and i < len(proc.io_events):
                fila.append(proc)
            elif proc.execucao_restante > 0:
                # Se o processo terminou a execução ou entrou em I/O, adiciona ele na fila novamente
                fila.append(proc)

            # Atualiza o tempo do escalonador
            self.turnarounds[proc.nome] = start_time - proc.ativacao
            self.tempo_atual = start_time  # Atualiza o tempo para o próximo processo

    def get_timeline(self):
        """
        Retorna a timeline completa de todos os processos.
        :return: Dicionário com o nome dos processos e seus respectivos eventos
        """
        return {proc.nome: proc.timeline for proc in self.processos}

# Função que cria uma barrinha Gantt no gráfico
def criar_barrinha_gantt(ax, processo, inicio, fim, tipo, posicao):
    """
    Cria uma barrinha de Gantt para um processo no gráfico.
    """
    cores = {"Execução": "skyblue", "I/O": "orange"}
    ax.barh(posicao, fim - inicio, left=inicio, color=cores[tipo], edgecolor="black")
    ax.text((inicio + fim) / 2, posicao, f"{inicio}-{fim}", ha="center", va="center", fontsize=8, color="black")

# Função que plota o gráfico Gantt
def plot_gantt(timeline, title):
    fig, ax = plt.subplots(figsize=(12, 6))
    y_labels = list(reversed(timeline.keys()))  # Inverter para P1 no topo e P5 embaixo
    ax.set_yticks(range(len(y_labels)))
    ax.set_yticklabels(y_labels)
    
    # Plotar as barrinhas de Gantt
    for i, proc in enumerate(y_labels):
        eventos = timeline[proc]
        for evento, start, end in eventos:
            criar_barrinha_gantt(ax, proc, start, end, evento, i)

    ax.xaxis.set_major_locator(MultipleLocator(4))  # Escala de 4 em 4 no eixo X para o quantum
    ax.set_xlabel("Tempo")
    ax.set_title(title)
    plt.grid(axis="x", linestyle="--", linewidth=0.5)
    
    # Adicionar legenda
    cores = {"Execução": "skyblue", "E/S": "orange"}
    handles = [plt.Line2D([0], [0], color=cores[label], lw=8) for label in cores]
    labels = cores.keys()
    ax.legend(handles, labels, title="Legenda", loc="upper right")
    plt.tight_layout()
    plt.show()


# Dados dos processos com I/O
processos = [
    Processo("P1", 13, 0, [(4, 7)]),
    Processo("P2", 11, 4, [(2, 7), (6, 4)]),
    Processo("P3", 7, 5, []),
    Processo("P4", 8, 7, []),
    Processo("P5", 12, 8, [(2, 4), (7, 7)]),
]

# Criando o escalonador Round-Robin com I/O e Quantum = 4
quantum = 4
escalonador_rr = Escalonador(processos, quantum)
escalonador_rr.escalonar()

# Obtendo a timeline dos processos
rr_timeline = escalonador_rr.get_timeline()
plot_gantt(rr_timeline, "Escalonamento Round-Robin")

print("Turnaround Round-Robin com I/O:", escalonador_rr.turnarounds)
