 - Trabalho Simulação de Propagação de Incêndios - 

1 - Introdução

A ideia do trabalho é simular uma propagação de incêndio em uma floresta, sendo esse processo influenciado por vários fatores, como a posição de árvores, áreas vazias, presença de água e a ação do vento. Durante um incêndio, o fogo irá se espalhar a partir de um local pré-definido e se movimentar através das árvores, transformando árvores saudáveis em chamas pelas direções ortogonais (cima, baixo, esquerda e direita), podendo, de acordo com as condições estabelecidas em um arquivo config.hpp, gerar diferentes cenários durante a propagação dentro de um número especifico de iterações maximas possiveis definidas no aruquivo config.hpp.

Além disso, o trabalho simula uma possível rota de fuga de um animal dentro dessa floresta, permitindo que ele se movimente em direções ortogonais, fugindo do fogo sempre que possível e se adaptando às diferentes situações que irão ocorrer durante a simulação.

O objetivo do trabalho é modelar essa simulação utilizando a linguagem C++, adotando a abordagem de que a floresta será representada por uma matriz quadrada, e que o fogo se espalhará alterando as coordenadas dessa matriz ao longo das iterações, ou seja, com o passar do tempo, as células da matriz estarão sujeitas a mudanças conforme o avanço da simulação.

2 Metodologia e Estudos de casos

A ideia nesse trabalho para solucionar o problema proposto e construir a modelagem foi incialemente apartir de três pilares, sendo esses a construção de um mapa, a propagação do fogo e a movimentação do animal

2.1 Construção do mapa

Para a construção do mapa utilizamos o conceito de matriz, uma vez que a floresta é representada por uma matriz, é necessario a criação de dois atributos para esse mapa que são as linhas e as colunas. Essas são criadas afim de definir o tamanho do mapa(floresta) com qual será trabalhada durante a simulação.

Além desses dois atributos, a utilização de mais dois atributos, sendo respectivamente responsavéis por armazenar a posição inicial do fogo e por onde ele começará a se espalhar.

Uma vez que esse trabalho é idealizado de forma a não ter que receber nenhuma informação de um usuario externo, foi necessario que essas informações fossem extraídas de um arquivo, arquivo esse o input.dat que tem seus 4 primeiros valores sendo responsaveis pelo o numero de linhas, coluna, posição incial do fogo no eixo x e no eixo y. Para que fosse extraido essas informações utilizamos o metodo Carregar mapa

2.1.1 Carregar mapa

O método carregarMapa tem como objetivo carregar os dados de um mapa a partir de um arquivo de entrada, arquivo esse definido no main como o arquivo "input.dat". Ele começa tentando abrir o arquivo especificado pelo nome input.dat. Se o arquivo não for aberto corretamente, exibe uma mensagem de erro e retorna sem fazer nada.

Ao abrir o arquivo com sucesso, o método lê as dimensões do mapa (número de linhas e colunas) e as coordenadas do fogo (fogoX e fogoY). Em seguida, a matriz que representa o mapa é redimensionada de acordo com as dimensões lidas, e os valores do mapa (representados por números inteiros esses podendo ser 0 1 2 3 4, sendo o 0(area vazia), sendo 1(arvore saudavel), 2(arvore queimando), 3 (arvore queimada), 4 (presença de agua)) carregados para dentro da matriz, linha por linha e coluna por coluna. Até que por fim, o arquivo seja fechado.

Esse processo permitiu que extraissimos as dimensões do mapa, e a posição incial do fogo.

2.1.2 Imprimir Mapa

A função imprimirMapa tem como propósito exibir a estrutura da matriz que representa o mapa da floresta, permitindo uma visualização clara e precisa do estado atual da simulação. Após a execução do método carregarMapa, a matriz é preenchida com valores inteiros que indicam o tipo de terreno em cada célula: áreas vazias, árvores saudáveis, árvores queimando, árvores queimadas ou a presença de água. Esses valores são distribuídos conforme as dimensões especificadas no arquivo de entrada, e a função de impressão facilita a verificação visual do conteúdo da matriz.

A função realiza uma iteração completa sobre as linhas da matriz, utilizando um laço de repetição (for) para acessar cada vetor representando uma linha do mapa. Dentro desse laço, outro laço percorre os elementos individuais de cada linha, imprimindo seus valores de maneira sequencial, com um espaço entre eles para garantir a clareza na leitura. Ao final de cada linha, o comando de nova linha é acionado, o que garante que os dados de cada linha apareçam de forma estruturada e alinhada.

2.2 Propagação do fogo

Para a propagação do fogo a ideia foi respeitar tudo que foi proposto no trabalho, sendo a proposta de espalhar o fogo de acordo com casos que haja vento e casos que não haja vento, a propagação deve ocorrer de uma arvore queimando (2) para uma arvore saudavel (1) e que uma arvore seria considerada queimada(3) após duas iterações queimando, pensando nisso a ideia foi inicialmente estabelecer condições para a propagação do fogo, podendo essas ser controladas no arquivo config.hpp apartir de 5 definições que recebem valores booleanos(true ou false) e após isso executar a simulação de forma que siga tudo que é estabelecido, tais como situações das possiveis movimentações do animal dentro da floresta e tudo que ele pode influenciar dentro dos valores do mapa.

2.2.1 Condições para propagar o fogo

As condições para propagar o fogo são definidas nos metodo podemPropagar,estaDentroDoLimite e o valor para qual ele vai propagar ser igual a 1.

Há 4 metodos com esse nome, sendo um metodo especifico para cada direção. esses metodos trabalham com as definições estabelecidas no config, fazendo com que o fogo só se propague para um direção se a presença de vento for false, sendo nesse o fogo espalhando para todas as direções, ou no caso da direção especifica tiver com vento para sua direção ativada como true. Podendo mudar essas definições dentro do arquivo config.hpp.

Além disso possui outro metodo que está localizado no arquivo Mapa.cpp que verifica se o valor no qual se deseja propagar o fogo esteja dentro dos limites do mapa, a posição deve estar entre os valores (0,0) e os valores lidos de (linhas,colunas). Caso isso não aconteça o fogo não irá propagar para aquele local.

2.2.2 Executar a propagação

Após estabelecermos condições para propagar o fogo, utilizamos dois vetores para controle das chamas que que vão queimar e que se considerão queimadas. Sendo respectivamente os vetores novasChamas e o vetor queimarProximaiteração.

2.2.2.1 Novas chamas 

Dentro do metodo executarSimulacao, temos dois laços de repetição que são responsaveis por passar por todos os valores da matriz e identificar o valores iguais a 2, ou seja suas coordenas x,y, que no casos são representados por i e j. Após isso apartir de operações com i e j sendo i-1, i+1, j-1 e j+1 caminhar para as 4 direções ortogonais em buscas de posições com quais o fogo possa sem propagar, porém para o fogo se propagar para uma dessas casas ele deve encaixar nas condições de propagação do fogo, ou seja , essa posição deve ter valor igual a 1, o vento tem que estar a favor dessa posição e essa posição não estar fora do mapa. 

Caso a posição seja valida e o fogo possa se propagar apartir dela também, armazenamos ela no vetor NovasChamas inserindo a mesma posição ao final do vetor com a utilização da função emplace_back da biblioteca (<vector>), após analisarmos todas as direções e vermos todas as posições que podem ter o fogo propagado apartir delas e colocarmos a mesma dentro do vetor novasChamas, ocorre a leitura de todas as posições desse vetor setando o valor 2 em todas essas posições , tornando assim arvores saudaveis, em arvores queimando. Após isso limpamos esse vetor para garantir que na proxima iteração ele trabalhe com posições diferentes.

2.2.2.2 Queimar proxima iteração

Criamos também um vetor chamado queimarProximaIteração e nele que as arvores que estão queimando se tornam arvores queimadas. Dentro dos dois laços for citados anteriormente , utilizamos novamente a função emplace_back que irá pegar todas as posições que estão com 2 naquele instante antes das novas chamas, e irá colocar os mesmos dentro do vetor queimarProximaIteração , no qual na proxima iteração serão queimados. Fazendo assim com que as arvores não passem diretamente de 2 para 3, mas sim durante uma das iterações só armazemanamos as posições que vão virar queimadas , para depois na proxima iteração fazer a passagem de 2 para 3.

2.3 Movimentações do animal

A ideia para a movimentação do animal foi começar o mesmo em uma posição definida no config , sendo utilizada duas constantes de inteiro ANIMAL_X para definir sua posição em relação ao eixo X e ANIMAL_Y para definir sua posiçaõ em relação ao eixo Y. Além disso também estabelecer condições para que ele se movimente, essas condições é que ele não saia do mapa, com isso utilizamos a função de estar dentro dos limites e a condição de ser uma região diferente de 2 ou seja , ele deve estar em casas, 4 0 1 ou 3 , sendo essa mesma ordem de prioridade tendo também como o pior dos casos voltar uma aréa que ele já pisou, foi considerado também os casos da dispersão da umidade , que no caso faria com que ao chegar em uma area com agua, a região fosse transformada em 0 e as casas vizinhas ortogonais fossem transformadas em 1 de acordo com a dispersão da umidade. Foi considerado também a possibilidade do animal poder também estar podendo ficar durante 3 iterações na mesma posição caso essa posição seja uma posição 0. Além disso fazer observações ao final sobre quantos passos o animal deu,caso ele morra em qual iteração morreu, o caminho que o mesmo percorreu para fugir do incendio e quantas vezes o mesmo encontrou agua e a opurtunidade do mesmo ter uma segunda chance em caso ele não esteja cercado pelo o fogo.

Para que ocorrese a movimentação animal , foi decidido modular bem o codigo , dividindo o movimento em varios metodos menores, de forma que ficasse mais facil de compreender.

2.3.1 Modulação da movimentação do animal em busca do melhor movimento

Inicialmente foi criado um metodo para verificar se a posição que o animal vai é uma posição possivel, esse metodo se chama PodeMoverPara, nele verificamos se a posição está dentro do mapa e não é uma posição que esteja queimando no momento.

Após isso criamos um vetor que terá como o intuito de armazenar quais posições o animal visitou durante o seu caminho, com esse vetor utilizamos as funções padrões find, begin e end da biblioteca de vetores que fazem com que encontre posições que estão dentro do vetor ou não. Utilizamos isso no metodo JaVisitada, retornando um valor true se já foi visitado e false se não.

Utilizando o retorno da função já visitada, estabelecmos um metodo de calcularPrioridade, esse mesmo faz com que posições que já foram visitadas tenha retorno 5, posições que já foram queimadas tenham retorno 3, posições de arvores  saudaveis tenha retorno 2, posições com area vazia tenha prioridade 1,e posições com agua sejam as prioritarias com retorno 0.

O método DirecoesPossiveis define as direções possíveis de movimento para o animal no mapa, retornando um vetor de pares de inteiros que representam os deslocamentos para as posições adjacentes (cima, baixo, esquerda e direita). Isso permite que o animal explore todas as direções ao seu redor durante o processo de movimentação.
 O método avaliarDirecao é responsável por verificar se uma direção é válida. Ele primeiro checa se o movimento para a posição (linha, coluna) é permitido usando o método podeMoverPara. Caso contrário, retorna uma prioridade alta 99, indicando que a posição não é viável. Se o movimento for válido, o método obtém o valor daquela posição especifica e verifica se ela foi visitada anteriormente com o método jaVisitada. Em seguida, calcula a prioridade da posição com o método calcularPrioridade, que leva em consideração o tipo da célula e seu status de visitação.

O método devePararBusca determina se a busca deve ser interrompida, considerando que uma prioridade igual a 0 indica que o animal encontrou uma posição ideal,ou seja encontrou agua. Se a prioridade de uma direção for 0, a busca é finalizada, pois essa posição é a melhor possível. O método encontrarMelhorMovimento é a principal função responsável por encontrar a melhor direção para o animal. Ele inicia com a posição atual como a melhor posição possível e, em seguida, avalia todas as direções possíveis, calculando as prioridades de cada uma delas. Se uma direção tem uma prioridade melhor ou seja um menor, ela se torna a nova melhor posição. Caso a prioridade seja 0, indicando que o animal encontrou uma posição ideal, a busca é interrompida. No final, o método retorna a posição com a melhor prioridade.

Esses metodos em conjunto permitem ao animal escolher sempre a melhor direção, com base nas prioridades, garantindo que ele se mova sempre em direção a uma posição mais favorável, quando a mesma estiver disponível. Após toda essa analise, pode se mover o animal para a melhor posição encontrada.

2.3.2 Mover o animal

Para mover o animal, antes de tudo analisa se o animal ainda está vivo, após isso criamos um inteiro para pegarmos a atual posição do animal, caso essa posição seja 0 , que é o caso que o animal pode ficar 3 iterações na mesma posição, definimos aquela posição como a de melhor movimento e ele fica nela, porém a cada iteração que ele fica nessa casa o numero de iterações sobre, sendo esse um contador criado para que cada iteração esse valor subisse, e no caso dele ficar maior que 3, ele fosse considerado o pior caso , forçando o animal a sair de lá e logo após zerando esse contador de iterações parado , para um caso que ele encontre uma nova posição 0.

Caso a nova posição seja diferente da posição atual, o animal se move para a nova célula, atualizando sua posição e adicionando-a ao vetor caminho utilizando novamente o emplace_back, e armazena o trajeto percorrido. Além disso, o contador de passos é somado mais um, registrando que mais um passo foi dado ao animal, podendo apartir desse vetor no final, saber exatamente quantos passos ele deu.

2.3.3 Umidade da agua

Para que a umidade da agua ocorra, incialmente estabelecemos as posições atuais em inteiros x e y, e fazemos uma verificação se a posição é igual a agua, se sim de imediato setamos o valor dela para 0, e logo após criamos um vetor chamado celulasParaConverter, após isso checamos todas as direções com operações x+1 , x-1, y+1,y-1, e verificamos se essas posições estão dentro dos limites do mapa , se sim utilizando o emplace_back novamente adicionamos essa posição no vetor celulasParaConverter. Depois de se analisar todos os casos lemos todas as posições que estavam dentro desse vetor e setamos as mesmas como 1.

O metodo que faz tudo isso se chama converterVizinhosParaArvore e ao final dele tem um contador que marca o encontrosComAgua, para que depois possamos saber quantas vezes agua foi encontrada. Esse metodo é chamado no final do metodo mover, e nele e a posição que o metodo mover escolher ir, que é a posição que é inicialmente verificada se é igual a 4.

2.3.4 Morte do animal

Quando o animal morre, o processo envolve várias verificações e mudanças de estado, com a finalidade de registrar o evento de sua morte e gerenciar o comportamento após esse evento. Primeiramente, temos o método estaEmPerigo, que verifica se o animal se encontra em uma posição de perigo, representada pela célula com valor . Caso o animal esteja nesta posição, o método retornará true.

Para que o animal tenha uma chance de escapar do perigo, existe o método temRotaDeFuga, que analisa se há ao menos uma direção para onde o animal possa se mover que não seja uma área perigosa (como o fogo, representado pelo valor 2). O método percorre as direções possíveis ao redor da posição do animal e, caso identifique uma direção válida, retorna true, indicando que há uma rota de fuga.

Já o método forcarFuga é utilizado quando o animal precisa urgentemente escapar. Ele busca a direção com a melhor prioridade entre as direções possíveis, levando em consideração as condições do mapa e as células ao redor. O animal será forçado a se mover para a posição mais segura, desde que seja válida, e o movimento será registrado no vetor de caminho.

Quando a morte do animal é inevitável, o método morrer é chamado. Esse método altera o estado do animal para vivo = false e registra a iteração em que ele morreu, o que é importante para o controle de eventos no jogo ou simulação.

Por fim, temos o método getIteracaoMorte, que retorna a iteração em que o animal morreu. Isso pode ser útil para fins de rastreamento ou para contabilizar os eventos no sistema, permitindo que se saiba exatamente quando o animal não resistiu ao ambiente hostil e sucumbiu.

Esses métodos, em conjunto, garantem que a morte do animal seja registrada adequadamente, proporcionando ao sistema as informações necessárias para tratar a morte de forma eficaz no contexto do simulador. Eles também lidam com a dinâmica de fuga do perigo e asseguram que o animal tenha a chance de escapar caso haja uma saída disponível. Ou seja em caso que o animal esteja em perigo, tentou rota de fuga, forçou uma rota de fuga e usou a segunda chance, ele será considerado como moro uma vez que ele não tem para aonde ir.

2.4 Saídas das simulação

No metodo executarSimulacao é aonde definimos como ocorrerá a saída da nossa simulação, nela definimos que toda vez que o metodo executar função um arquivo output.dat será criado e com o clearFile, limpe tudo que estava escrito nesse arquivo anteriormente. Para utilizar o clearFile foi utilizado a biblioteca <fstream> que permitiu também a leitura e a escrita nos arquivos. 

Poreḿ antes de criamos o mapa estabelecemos através de um laço de repetição for que o , dura até o número maximo de iteraçõse estabelecidos no config, caso essa iteração chegue ao final o arquivo é fechado, e a simulação acaba, a simulação também acabará quando os vetores novasChamas e queimarProximaIteração estiverem vazios uma vez que o incendio acabou e não há casas possiveis para se mover.

Uma vez que o arquivo é aberto imprimimos uma mensagem escrito iteracao, que ao lado terá o numero da iteração no qual a simulação está para acompanhar da melhor forma, abaixo teremos como a matriz está naquele presente momento, e as informações tais como a ultima posição do animal, ou seja a que ele ficou após aquela iteração, o status do mesmo que enquanto não estiver nas condições de morte é considerado fixo como vivo, a quatidade de passos e de encontros com agua definido pelos dois contadores. Esses resultado irão aparecer iteração por iteração até que por fim, por algum dos motivos citados o arquivo se feche, porém antes do arquivo fechar o arquivo lê e imprime o vetor caminho criado anteriormente mostrando os passos do animal, e em caso de morte do mesmo em qual iteração ele morreu. 

3 Conclusão


O projeto conseguiu atingir o objetivo de simular a propagação de um incêndio e a movimentação de um animal tentando escapar. O fogo foi espalhado de maneira controlada usando vetores que guardavam as próximas posições que deveriam queimar, e o animal se movimentou tentando encontrar o melhor caminho para fugir, priorizando áreas seguras.

A lógica de propagação do fogo e de movimentação foi feita de forma a garantir que o mapa fosse atualizado corretamente a cada iteração, respeitando os limites e as condições do ambiente. O animal tomava decisões baseado nas direções disponíveis, tentando sempre se afastar do fogo.

Apesar do projeto estar funcionando bem, seria possível melhorar algumas coisas, como adicionar tratamentos de erros, uma vez que uma pessoa que a pessoa não consiga confiurar a matriz do jeito correto ou o config da maneira certa, seria bom que aparecesse quais error cometidos e como concerta-lo, na implemtação só há um caso que isso é feito que é no caso do animal nascer no mesmo local do fogo , fazendo assim com que seja impressa uma mensagem avisando o que aconteceu, e por fim melhorar mais ainda a modularização do codigo em algumas partes, para ficar mais intuitivo no geral.

4 Referências

Aula_02_-_Introducao_ao_C.pdf
Aula_03_-_Introduo_a_OO.pdf
Aula_14_-_Tratamento_de_Excees.pdf
Aula_13_-_stl.pdf
Aula_10_OO_com_Lista_fila_pilha.pdf

5 Modo de compilação

Deve se utilizar uma matriz que seja do exato tamanho definido para ela, ou seja não pode utilizar uma matriz maior que os tamanhos estabelecidos e nem menor, além a posição do fogo deve estar de acordo com a posição especificada. Para especificar a quantidade de linhas , coluna , fogox e fogoy. É somente definir os 4 primeiros valores para que sejam nessa mesma ordem responsavel por cada uma das caracteristicas a se especificar no mapa. Além disso deve dar valore booleanos para #define VENTO_NORTE , #define VENTO_SUL   #define VENTO_LESTE #define VENTO_OESTE #define SEGUNDA_CHANCE e #define VENTO_ATIVO. E valores inteiros para a posição inicial do animal e a quantidade de iterações que deve haver durante a simulação.

Uma vez que o arquivo está com o makefile, deve seguir a ordem de que toda vez ao compilar, esteja make clean, make, e make run

6 Autor

Luiz Fernando dos Santos Queiroz







