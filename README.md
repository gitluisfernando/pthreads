# pthreads
Trabalho 1 - INE5611 - SO - UFSC

Trabalho sobre IPC

Motivação

• Exercitar o uso de primitivas para comunicação entre processos (IPC)
• Implementação de uma aplicação de brinquedo utilizando C e chamadas ao sistema para IPC
• Uso de pthreads e mecanismos de sincronização
• Exercitar o uso de mecanismos de sincronização entre processos para implementar regiões críticas

Descrição do trabalho

• Desenvolver uma aplicação para o cadastro de “itens” (no caso, músicas), seguindo o modelo produtor/consumidor
• O sistema será composto por:
• Um processo produtor (multithreaded);
• N processos consumidores (supostamente seriam tocadores de mp3, editores de áudio, etc.);
• Cada consumidor deve imprimir na tela um registro de log das músicas consumidas ao longo da sua execução

Requisitos

• O produtor deve ser uma implementação multithreaded
• Várias threads são responsáveis por criar músicas
• Utilizar a biblioteca pthread
• A comunicação entre produtor e consumidor é de escolha livre, sendo possível utilizar memória compartilhada ou filas de mensagens
• Utilizar a operação pipe ( | ) disponível pelo SO para filtrar informações sobre as músicas. 
• Ex.: Mostrar apenas músicas de um gênero ou autor
• Dica: usar comandos como o grep para filtrar informações
• O acesso à regiões críticas deve ser feito em exclusão mútua
• Usar estruturas como semáforos, mutex, monitores para garantir a consistência dos dados
