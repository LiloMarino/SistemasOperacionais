import matplotlib.pyplot as plt
from matplotlib.ticker import MultipleLocator

class Processo:
    def __init__(self, nome: str, execucao: int, ativacao: int, io_events: list[tuple[int, int]]):
        self.nome = nome
        self.execucao = execucao  # Tempo total de execução
        self.ativacao = ativacao  # Tempo em que o processo é ativado
        self.io_events = io_events  # Lista de eventos de I/O (tuples com tempo de início e duração)
        self.execucao_restante = execucao  # Tempo restante de execução
        self.actual_io = 0  # Índice para o próximo evento de I/O
        self.timeline = []  # Lista para armazenar a timeline do processo

    def processar_io(self, start_time, end_time):
        """
        Adiciona um evento de I/O à timeline do processo.
        :param start_time: Tempo de início da execução de I/O
        :param end_time: Tempo de término da execução de I/O
        :return: Nenhum valor retornado, apenas atualiza a timeline.
        """
        self.timeline.append(("I/O", start_time, end_time))

    def processar_execucao(self, start_time, end_time):
        """
        Adiciona um evento de Execução à timeline do processo.
        :param start_time: Tempo de início da execução
        :param end_time: Tempo de término da execução
        :return: Nenhum valor retornado, apenas atualiza a timeline.
        """
        self.execucao_restante -= end_time - start_time
        self.timeline.append(("Execução", start_time, end_time))

    def next_io(self):
        """
        Retorna o próximo evento de I/O do processo.
        :return: O próximo evento de I/O ou None se não houver mais eventos.
        """
        if self.actual_io < len(self.io_events):
            return self.io_events[self.actual_io]
        return None  # Se não houver mais eventos de I/O, retorna None

    def processar_next_io(self):
        """
        Avança para o próximo evento de I/O.
        :return: Nenhum valor retornado, apenas avança para o próximo evento de I/O.
        """
        if self.actual_io < len(self.io_events):
            self.actual_io += 1

    @property
    def tempo_executado(self):
        """
        Calcula o tempo total já executado pelo processo, baseado na timeline.
        :return: O tempo total de execução (int).
        """
        return self.execucao - self.execucao_restante


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
            processo : Processo = fila.pop(0)
            quantum_start = max(self.tempo_atual, processo.ativacao)
            quantum = min(self.quantum, processo.execucao_restante)
            quantum_end = quantum_start + quantum
            io = processo.next_io()
            if io and io[0] <= processo.tempo_executado + quantum:
                quantum_end = quantum_start + (io[0] - processo.tempo_executado)
                processo.processar_execucao(quantum_start, quantum_end)
                processo.processar_next_io()
                processo.processar_io(quantum_end, quantum_end+io[1])
            else:
                processo.processar_execucao(quantum_start, quantum_end)

            if processo.execucao_restante > 0:
                fila.append(processo)

            # Atualiza o tempo do escalonador
            self.turnarounds[processo.nome] = quantum_start - processo.ativacao
            self.tempo_atual = quantum_end

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

    ax.xaxis.set_major_locator(MultipleLocator(5))  # Escala de 4 em 4 no eixo X para o quantum
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
    Processo("P2", 11, 4, [(2, 4), (6, 7)]),
    Processo("P3", 7, 5, []),
    Processo("P4", 8, 7, []),
    Processo("P5", 12, 8, [(2, 7), (7, 4)]),
]

# Criando o escalonador Round-Robin com I/O e Quantum = 4
quantum = 4
escalonador_rr = Escalonador(processos, quantum)
escalonador_rr.escalonar()

# Obtendo a timeline dos processos
rr_timeline = escalonador_rr.get_timeline()
plot_gantt(rr_timeline, "Escalonamento Round-Robin")

print("Turnaround Round-Robin com I/O:", escalonador_rr.turnarounds)
