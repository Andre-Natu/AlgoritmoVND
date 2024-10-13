
# AlgoritmoVND

Um algoritmoVND com meta-heuristica ILS em c++ para resolver um problema de Single Machine Scheduling with Sequence-Dependent Setup Times and Due Dates. Feito para a disciplina de APA(Análise e Projeto de
Algoritmos).

## Vizinhanças Usadas:

- Algoritmo Guloso para geração da solução inicial
- Swap Adjacente e completo para vizinhança 1
- 2-opt para a vizinhança 2
- Re-insert para a vizinhança 3

## Autor

- [@Andre-Natu](https://www.github.com/Andre-Natu)

## Descrição completa do problema

Seja nn o número de pedidos que devem ser processados em um determinado dia na linha de produção da fábrica. Cada pedido i∈{1,…,n}i∈{1,…,n} requer um tempo titi​ (em minutos) para ser processado e deve ser concluído até o tempo pipi​. Entre o processamento de dois pedidos, pode ser necessário a limpeza e/ou adequação do tipo de embalagem. Sendo assim, consideramos que sijsij​ especifica o tempo (em minutos) necessário para preparar a linha de produção para processar o pedido jj logo após o pedido ii, onde i,j∈{1,…,n}i,j∈{1,…,n} e i≠ji=j. Note que, caso o pedido jj seja o primeiro a ser processado na linha de produção, é necessário considerar o tempo s0js0j​ para preparar a linha. Caso um pedido ii seja finalizado após o tempo pipi​, a empresa paga uma multa por atraso Mi=wi×(Ci−pi)Mi​=wi​×(Ci​−pi​), onde CiCi​ especifica o tempo de término do processamento do pedido ii e wiwi​ determina o valor da multa por minuto de atraso associada ao pedido ii. O objetivo do problema é obter a sequência de processamento dos pedidos na linha de produção de forma a garantir que todos os pedidos sejam processados e que a soma das multas por atraso seja mínima.

