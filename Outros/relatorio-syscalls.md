# Relatório do Programa - Grupo B

**Nome do Aluno: Murilo Aldigueri Marino**

## Log de saída do `strace`

```
$ strace ./meuPrograma               
execve("./meuPrograma", ["./meuPrograma"], 0x7ffd131ee970 /* 38 vars */) = 0
brk(NULL)                               = 0x55a7f7daf000
arch_prctl(0x3001 /* ARCH_??? */, 0x7ffd68da7f40) = -1 EINVAL (Invalid argument)
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fcdcc036000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=62671, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 62671, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7fcdcc026000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libstdc++.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=2260296, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 2275520, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7fcdcbdfa000
mprotect(0x7fcdcbe94000, 1576960, PROT_NONE) = 0
mmap(0x7fcdcbe94000, 1118208, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x9a000) = 0x7fcdcbe94000
mmap(0x7fcdcbfa5000, 454656, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1ab000) = 0x7fcdcbfa5000
mmap(0x7fcdcc015000, 57344, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x21a000) = 0x7fcdcc015000
mmap(0x7fcdcc023000, 10432, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7fcdcc023000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libgcc_s.so.1", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=125488, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 127720, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7fcdcbdda000
mmap(0x7fcdcbddd000, 94208, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x3000) = 0x7fcdcbddd000
mmap(0x7fcdcbdf4000, 16384, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1a000) = 0x7fcdcbdf4000
mmap(0x7fcdcbdf8000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1d000) = 0x7fcdcbdf8000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0P\237\2\0\0\0\0\0"..., 832) = 832
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
pread64(3, "\4\0\0\0 \0\0\0\5\0\0\0GNU\0\2\0\0\300\4\0\0\0\3\0\0\0\0\0\0\0"..., 48, 848) = 48
pread64(3, "\4\0\0\0\24\0\0\0\3\0\0\0GNU\0I\17\357\204\3$\f\221\2039x\324\224\323\236S"..., 68, 896) = 68
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=2220400, ...}, AT_EMPTY_PATH) = 0
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
mmap(NULL, 2264656, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7fcdcbbb1000
mprotect(0x7fcdcbbd9000, 2023424, PROT_NONE) = 0
mmap(0x7fcdcbbd9000, 1658880, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x28000) = 0x7fcdcbbd9000
mmap(0x7fcdcbd6e000, 360448, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1bd000) = 0x7fcdcbd6e000
mmap(0x7fcdcbdc7000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x215000) = 0x7fcdcbdc7000
mmap(0x7fcdcbdcd000, 52816, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7fcdcbdcd000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libm.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=940560, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 942344, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7fcdcbaca000
mmap(0x7fcdcbad8000, 507904, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0xe000) = 0x7fcdcbad8000
mmap(0x7fcdcbb54000, 372736, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x8a000) = 0x7fcdcbb54000
mmap(0x7fcdcbbaf000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0xe4000) = 0x7fcdcbbaf000
close(3)                                = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fcdcbac8000
arch_prctl(ARCH_SET_FS, 0x7fcdcbac93c0) = 0
set_tid_address(0x7fcdcbac9690)         = 5269
set_robust_list(0x7fcdcbac96a0, 24)     = 0
rseq(0x7fcdcbac9d60, 0x20, 0, 0x53053053) = 0
mprotect(0x7fcdcbdc7000, 16384, PROT_READ) = 0
mprotect(0x7fcdcbbaf000, 4096, PROT_READ) = 0
mprotect(0x7fcdcbdf8000, 4096, PROT_READ) = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fcdcbac6000
mprotect(0x7fcdcc015000, 45056, PROT_READ) = 0
mprotect(0x55a7cb9e2000, 4096, PROT_READ) = 0
mprotect(0x7fcdcc070000, 8192, PROT_READ) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
munmap(0x7fcdcc026000, 62671)           = 0
getrandom("\xca\x9a\x5b\x53\xfe\x88\x64\xce", 8, GRND_NONBLOCK) = 8
brk(NULL)                               = 0x55a7f7daf000
brk(0x55a7f7dd0000)                     = 0x55a7f7dd0000
futex(0x7fcdcc02377c, FUTEX_WAKE_PRIVATE, 2147483647) = 0
openat(AT_FDCWD, "source.html", O_RDONLY) = 3
openat(AT_FDCWD, "dest.html", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 4
read(3, "<!DOCTYPE html>\n<html lang=\"en\">"..., 8191) = 427
read(3, "", 8191)                       = 0
newfstatat(1, "", {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0x1), ...}, AT_EMPTY_PATH) = 0
write(1, "C\303\263pia conclu\303\255da com sucesso!\n", 31Cópia concluída com sucesso!
) = 31
close(3)                                = 0
write(4, "<!DOCTYPE html>\n<html lang=\"en\">"..., 427) = 427
close(4)                                = 0
exit_group(0)                           = ?
+++ exited with 0 +++
```

## Análise das Chamadas de Sistema

| **Chamada**       | **Descrição**                                                                                                      |
| ----------------- | ------------------------------------------------------------------------------------------------------------------ |
| `execve`          | Executa o programa `meuPrograma` no processo atual.                                                                |
| `brk`             | Aloca ou desaloca memória no heap para o processo.                                                                 |
| `arch_prctl`      | Configura propriedades específicas da arquitetura, como o registrador FS.                                          |
| `mmap`            | Mapeia arquivos ou dispositivos na memória, usado para alocar espaço.                                              |
| `access`          | Verifica a existência e permissões de acesso de um arquivo.                                                        |
| `openat`          | Abre um arquivo relativo a um diretório.                                                                           |
| `read`            | Lê dados de um arquivo ou entrada, utilizado para ler o arquivo de origem.                                         |
| `write`           | Escreve dados em um arquivo ou saída, utilizado para escrever no arquivo de destino.                               |
| `close`           | Fecha um descritor de arquivo.                                                                                     |
| `newfstatat`      | Obtém informações sobre um arquivo (tamanho, permissões).                                                          |
| `mprotect`        | Configura permissões de acesso à memória (leitura, escrita, execução).                                             |
| `prlimit64`       | Define ou consulta limites de recursos do processo, como limite de stack.                                          |
| `getrandom`       | Gera números aleatórios.                                                                                           |
| `futex`           | Utilizado para sincronização entre threads.                                                                        |
| `pread64`         | Lê dados de um arquivo em uma posição específica, usado para evitar movimentação do cursor.                        |
| `munmap`          | Desfaz um mapeamento de memória, liberando o espaço alocado.                                                       |
| `set_tid_address` | Define o endereço de um identificador de thread, usado para gerenciamento de threads.                              |
| `set_robust_list` | Define a lista de mutexes robustos para recuperação de falhas de threads.                                          |
| `rseq`            | Inicia e gerencia o registro de sequência em um processo, permitindo que threads registrem seu estado de execução. |
| `exit_group`      | Finaliza o programa e todos os threads associados.                                                                 |

## Referência

syscalls(2) - Linux manual page. Disponível em: <https://man7.org/linux/man-pages/man2/syscalls.2.html>. Acesso em: 14 nov. 2024.
