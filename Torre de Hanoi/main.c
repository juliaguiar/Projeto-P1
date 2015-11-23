#include <allegro.h>

#include <stdio.h>
#include <winalleg.h>
#include <string.h>
#include <ctype.h>

volatile int exit_program;
//FUNCÃO PARA FECHAR O JOGO
void fecha_programa() { exit_program = TRUE; }
END_OF_FUNCTION(fecha_programa)

volatile int timer;
//FUNÇÃO QUE RETORNA O TEMPO DO JOGO
void timer_counter() { timer++; }
END_OF_FUNCTION(timer_counter)

int screen_state;
int quant_discos;
int disco_movido;
int pontuacao;
char resultado[10];

//INSTALAÇÃO DAS FUNÇÕES PRINCIPAIS DA BIBLIOTECA GRÁFICA
void init()
{
  allegro_init();
  install_timer();
  install_mouse();
  install_keyboard();
  //install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
  set_color_depth(32);
  set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
  set_window_title("Torre de Hanói");

  exit_program = FALSE;
  LOCK_FUNCTION(fecha_programa);
  LOCK_VARIABLE(exit_program);
  set_close_button_callback(fecha_programa);

  timer = 0;
  LOCK_FUNCTION(timer_counter);
  LOCK_VARIABLE(timer);
  install_int_ex(timer_counter, BPS_TO_TIMER(60));

  screen_state = 1;
}


//TELA DO MENU
void mainmenu(){

  int exit_screen = FALSE;

  ///FONTS: INSTALAÇÃO DAS FONTES USADAS
  FONT* sketch50 = load_font("fontes/fonteSM50.pcx", NULL, NULL);
  FONT* sketch80 = load_font("fontes/fonteSM80.pcx", NULL, NULL);

  ///BITMAPS: INSTALAÇÃO DOS "OBJETOS" UTILIZADOS
  BITMAP* cursor = load_bitmap("imagens/cursor.BMP", NULL);
  BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);

  ///VARIÁVEIS
  int i, i2, i3;

  ///GAME LOOP
  //a variável "exit_program" controla o fechamento do programa
  //a variável "exit_screen" controla a saída de determinada tela do jogo
  //a variável "timer" controla a repetição do jogo em determinado tempo
    //com o objetivo de que o jogo rode com a mesma velocidade em qualquer máquina
  while(!exit_program && !exit_screen)
  {
      while(timer > 0 && !exit_program && !exit_screen)
      {
        //INPUT
        if(key[KEY_ESC])
         fecha_programa();

        //UPDATE

        //FUNÇÃO DO BOTÃO "INICIAR"
        //verifica onde está o cursor do mouse
        if(mouse_x > 200 && mouse_x < 200 + text_length(sketch50, "Iniciar")
           && mouse_y > 250 && mouse_y < 250 + text_height(sketch50))
        {

          //efeito highlight na elipse
          ellipsefill(buffer, 200 + text_length(sketch50, "Iniciar")/2, 250 + text_height(sketch50)/2, 105, 45, makecol(128,64,0));

          //verifica se o botão esquerdo do mouse está clicado
          //a variável "exit_screen" retorna TRUE para que saia da tela atual
          //a variável "screen_state" retorna a próxima tela
          if(mouse_b == 1)
          {
              exit_screen = TRUE;
              screen_state = 2;
              Sleep(300);
          }

        }

        //FUNÇÃO DO BOTÃO "AJUDA"
        if(mouse_x > 210 && mouse_x < 210 + text_length(sketch50, "Ajuda")
           && mouse_y > 400 && mouse_y < 400 + text_height(sketch50))
        {

          ellipsefill(buffer, 210 + text_length(sketch50, "Ajuda")/2, 400 + text_height(sketch50)/2, 105, 45, makecol(128,64,0));

          if(mouse_b == 1)
          {
              exit_screen = TRUE;
              screen_state = 4;
              Sleep(300);
          }

        }

        //DRAW

        //NOME DO JOGO
        textout_centre_ex(buffer, sketch80, "Torre de Hanoi", SCREEN_W/2, 80, makecol(255,0,0), -1);

        //DESENHO DO BOTÃO "INICIAR"
        ellipsefill(buffer, 200 + text_length(sketch50, "Iniciar")/2, 250 + text_height(sketch50)/2, 100, 40, makecol(210,105,0));
        textout_ex(buffer, sketch50, "Iniciar", 200, 250, makecol(128,64,0), -1);

        //DESENHO DO BOTÃO "AJUDA"
        ellipsefill(buffer, 210 + text_length(sketch50, "Ajuda")/2, 400 + text_height(sketch50)/2, 100, 40, makecol(210,105,0));
        textout_ex(buffer, sketch50, "Ajuda", 210, 400, makecol(128,64,0), -1);

        //DESENHO DA TORRE DE HANOI
        rectfill(buffer, 592, 205, 608, 251, makecol(128,128,128));
        rectfill(buffer, 595, 208, 605, 248, makecol(255,167,79));
        i2 = 25;
        i3 = 260;
        for(i = 10; i <= 20; i = i + 2){
            ellipsefill(buffer, 600, i3, i2, i, makecol(128,128,128));
            ellipsefill(buffer, 600, i3, i2-5, i-5, makecol(255,167,79));

            i2 += 15;
            i3 += i * 2 + 2;
        }
        rectfill(buffer, 480, 430, 720, 480, makecol(128,128,128));
        rectfill(buffer, 485, 435, 715, 475, makecol(255,167,79));

        //DESENHO DOS BITMAPS INSTALADOS
        draw_sprite(buffer, cursor, mouse_x-6, mouse_y);
        draw_sprite(screen, buffer, 0, 0);

        clear_to_color(buffer, makecol(255,167,79));

      }

  }

      ///FINALIZACAO
      destroy_font(sketch80);
      destroy_font(sketch50);
      destroy_bitmap(cursor);
      destroy_bitmap(buffer);

}

//TELA DA QUANTIDADES DE DISCOS (NÍVEL DO JOGO)
void escolha_nivel(){

int exit_screen = FALSE;

    ///FONTS
    FONT* sketch40 = load_font("fontes/fonteSM40.pcx", NULL, NULL);

    ///BITMAPS
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* cursor = load_bitmap("imagens/cursor.BMP", NULL);

    ///VARIÁVEIS
    int i, quant, cont;

    ///GAME LOOP
    while(!exit_program && !exit_screen)
    {
        while(timer > 0 && !exit_program && !exit_screen)
        {
        //INPUT
        if(key[KEY_ESC])
        fecha_programa();

        //UPDATE

        //FUNÇÃO DOS 6 BOTÕES
        cont = 3;
        for(i = 180; i <= 480; i = i + 50){
                if(mouse_x > 330 && mouse_x < 450
                && mouse_y > i - 20 && mouse_y < i + 20){

                    ellipsefill(buffer, 390, i, 65, 25, makecol(0,0,0));

                    if(mouse_b == 1)
                    {
                        quant_discos = cont;
                        exit_screen = TRUE;
                        screen_state = 3;
                    }

                }
        cont++;
        }

        //DRAW

        //TÍTULO NA TELA
        textout_ex(buffer, sketch40, "N. de discos:", 280, 100, makecol(204,204,0), -1);

        //DESENHO DOS BOTÕES DE NÍVEIS
        quant = 180;
        for(i = 3; i <= 8; i++){
            ellipsefill(buffer, 390, quant, 60, 20, makecol(128,0,0));
            textprintf_ex(buffer, sketch40, 385, quant-20, makecol(0,0,0), -1, "%d", i);
            quant += 50;
        }

        //DESENHO DOS BITMAPS INSTALADOS
        draw_sprite(buffer, cursor, mouse_x-6, mouse_y);
        draw_sprite(screen, buffer, 0, 0);

        clear_to_color(buffer, makecol(221,111,0));

        }
    }

    ///FINALIZACAO
    destroy_font(sketch40);
    destroy_bitmap(buffer);
    destroy_bitmap(cursor);

}

//TELA DE JOGO
void jogo()
{
    int exit_screen = FALSE;

    ///FONTS
    FONT* agentorange15 = load_font("fontes/fonteAO15.pcx", NULL, NULL);
    FONT* agentorange20 = load_font("fontes/fonteAO20.pcx", NULL, NULL);
    FONT* skater50 = load_font("fontes/fonteSGR50.pcx", NULL, NULL);

    ///BITMAPS
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* cursor = load_bitmap("imagens/cursor.BMP", NULL);
    BITMAP* pinos = load_bitmap("imagens/pinos.BMP", NULL);
    BITMAP* disco[8] = {load_bitmap("imagens/disco1.bmp", NULL),
                        load_bitmap("imagens/disco2.bmp", NULL),
                        load_bitmap("imagens/disco3.bmp", NULL),
                        load_bitmap("imagens/disco4.bmp", NULL),
                        load_bitmap("imagens/disco5.bmp", NULL),
                        load_bitmap("imagens/disco6.bmp", NULL),
                        load_bitmap("imagens/disco7.bmp", NULL),
                        load_bitmap("imagens/disco8.bmp", NULL)
                        };

    ///VARIÁVEIS
    int pinos_posicao[3][2] = {
                                {307, 459},
                                {499, 459},
                                {692, 459}
                              };
    int discos_posicao[8][2];
    int discos_tamanho[8][2] = {
                                {52, 22},
                                {62, 22},
                                {72, 23},
                                {81 ,22},
                                {91, 23},
                                {101, 23},
                                {112, 23},
                                {122, 24}
                               };

    int empilhamento[3][10] = {
                              {quant_discos, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 459},
                              {0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 459},
                              {0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 459}
                              };

    int disco_pino[quant_discos];

    int disco_solto = 0, movimentos = 0;

    int mov_minimo;
    switch(quant_discos){

        case 3: mov_minimo = 7;
                break;
        case 4: mov_minimo = 15;
                break;
        case 5: mov_minimo = 31;
                break;
        case 6: mov_minimo = 63;
                break;
        case 7: mov_minimo = 127;
                break;
        case 8: mov_minimo = 255;
                break;

    }

    int i, aux, boolean;

    int i2 = 1;

    //DESENHO INICIAL DOS DISCOS NO 1º PINO
    for (i = quant_discos-1; i >= 0; i--){

        discos_posicao[i][0] = pinos_posicao[0][0]-discos_tamanho[i][0]/2;
        discos_posicao[i][1] = empilhamento[0][9]-discos_tamanho[i][1];
        empilhamento[0][9] -= discos_tamanho[i][1];

        disco_pino[i] = 0;
        empilhamento[0][i2] = i;
        i2++;

    }

    ///GAME LOOP
    while(!exit_program && !exit_screen)
    {
        while(timer > 0 && !exit_program && !exit_screen)
        {
            //INPUT
            if(key[KEY_ESC])
            fecha_programa();

            //UPDATE

            //FUNÇÃO DO BOTÃO "REINICIAR"
            if(mouse_x > 40 && mouse_x < 40 + text_length(agentorange20, "Reiniciar")
              && mouse_y > 40 && mouse_y < 40 + text_height(agentorange20)){

                ellipsefill(buffer, 100, 50, 85, 35, makecol(0,0,0));

                if(mouse_b == 1)
                {

                    exit_screen = TRUE;
                    screen_state = 5;

                }

            }

            //FUNÇÃO DO BOTÃO "MENU"
            if(mouse_x > 75 && mouse_x < 75 + text_length(agentorange15, "MENU")
              && mouse_y > 520 && mouse_y < 520 + text_height(agentorange15)){

                if(mouse_b == 1)
                {

                    exit_screen = TRUE;
                    screen_state = 1;

                }

            }

            //DESALOCAÇÃO DO DISCO NO PINO
            if(disco_solto == 0){

                //verifica o disco de cima de cada pino
                for(i = 0; i < 3; i++){

                    if(empilhamento[i][0] != 0){

                        aux = empilhamento[i][empilhamento[i][0]];

                        //encostar no disco
                        if(mouse_x > discos_posicao[aux][0] && mouse_x < discos_posicao[aux][0] + discos_tamanho[aux][0]
                          && mouse_y > discos_posicao[aux][1] && mouse_y < discos_posicao[aux][1] + discos_tamanho[aux][1]){

                            int *DP = discos_posicao[aux], *DT = discos_tamanho[aux];

                            if(mouse_b == 1){

                                //se ainda não desempilhou
                                if(empilhamento[disco_pino[aux]][0] != 0 && empilhamento[disco_pino[aux]][empilhamento[disco_pino[aux]][0]] == aux){

                                        //desempilha um
                                        empilhamento[disco_pino[aux]][empilhamento[disco_pino[aux]][0]] = NULL;
                                        empilhamento[disco_pino[aux]][0]--;
                                        empilhamento[disco_pino[aux]][9] += DT[1];

                                        disco_solto = aux + 1;

                                }

                            }

                        }

                    }

                }

            }

            //ALOCAMENTO DO DISCO NO PINO
            if(disco_solto != 0){

            aux = disco_solto - 1;

            int *DP = discos_posicao[aux], *DT = discos_tamanho[aux];

                if(mouse_b == 1){

                //movimentação do disco pelo mouse
                DP[0] = mouse_x - DT[0]/2;
                DP[1] = mouse_y - DT[1]/2;

                }else{

                    //encostar no 1º pino
                    if(DP[0] > 298 - DT[0] && DP[0] < 312
                      && DP[1] > 141 && DP[1] < 459){

                        //verifica se pode alocar em pino diferente do de origem
                        if(disco_pino[aux] != 0 && (empilhamento[0][empilhamento[0][0]] >= aux || empilhamento[0][0] == 0)){

                            boolean = 1;

                        }else{

                            boolean = 0;

                            DP[0] = pinos_posicao[disco_pino[aux]][0] - DT[0]/2;
                            DP[1] = empilhamento[disco_pino[aux]][9] - DT[1];

                            empilhamento[disco_pino[aux]][0]++;
                            empilhamento[disco_pino[aux]][empilhamento[disco_pino[aux]][0]] = aux;
                            empilhamento[disco_pino[aux]][9] -= DT[1];

                        }

                        //também verifica se pode realocar no pino de origem
                        if((disco_pino[aux] == 0 && (empilhamento[0][empilhamento[0][0]] != aux
                                                    || (empilhamento[0][empilhamento[0][0]] == aux && empilhamento[0][0] == 0)))
                           || boolean){

                            DP[0] = pinos_posicao[0][0] - DT[0]/2;
                            DP[1] = empilhamento[0][9] - DT[1];

                            //empilha um
                            empilhamento[0][0]++;
                            empilhamento[0][empilhamento[0][0]] = aux;
                            empilhamento[0][9] -= DT[1];

                            disco_pino[aux] = 0;

                        }

                    //encostar no 2º pino
                    }else if(DP[0] > 492 - DT[0] && DP[0] < 506
                            && DP[1] > 141 && DP[1] < 459){


                        if(disco_pino[aux] != 1 && (empilhamento[1][empilhamento[1][0]] >= aux || empilhamento[1][0] == 0)){

                            boolean = 1;

                        }else{

                            boolean = 0;

                            DP[0] = pinos_posicao[disco_pino[aux]][0] - DT[0]/2;
                            DP[1] = empilhamento[disco_pino[aux]][9] - DT[1];

                            empilhamento[disco_pino[aux]][0]++;
                            empilhamento[disco_pino[aux]][empilhamento[disco_pino[aux]][0]] = aux;
                            empilhamento[disco_pino[aux]][9] -= DT[1];

                        }

                        if((disco_pino[aux] == 1 && (empilhamento[1][empilhamento[1][0]] != aux
                                                    || (empilhamento[1][empilhamento[1][0]] == aux && empilhamento[1][0] == 0)))
                           || boolean){

                            DP[0] = pinos_posicao[1][0] - DT[0]/2;
                            DP[1] = empilhamento[1][9] - DT[1];

                            empilhamento[1][0]++;
                            empilhamento[1][empilhamento[1][0]] = aux;
                            empilhamento[1][9] -= DT[1];

                            disco_pino[aux] = 1;

                        }

                    //encostar no 3º pino
                    }else if(DP[0] > 684 - DT[0] && DP[0] < 698
                            && DP[1] > 141 && DP[1] < 459){


                        if(disco_pino[aux] != 2 && (empilhamento[2][empilhamento[2][0]] >= aux || empilhamento[2][0] == 0)){

                            boolean = 1;

                        }else{

                            boolean = 0;

                            DP[0] = pinos_posicao[disco_pino[aux]][0] - DT[0]/2;
                            DP[1] = empilhamento[disco_pino[aux]][9] - DT[1];

                            empilhamento[disco_pino[aux]][0]++;
                            empilhamento[disco_pino[aux]][empilhamento[disco_pino[aux]][0]] = aux;
                            empilhamento[disco_pino[aux]][9] -= DT[1];

                        }

                        if((disco_pino[aux] == 2 && (empilhamento[2][empilhamento[2][0]] != aux
                                                    || (empilhamento[2][empilhamento[2][0]] == aux && empilhamento[2][0] == 0)))
                           || boolean){

                            DP[0] = pinos_posicao[2][0] - DT[0]/2;
                            DP[1] = empilhamento[2][9] - DT[1];

                            empilhamento[2][0]++;
                            empilhamento[2][empilhamento[2][0]] = aux;
                            empilhamento[2][9] -= DT[1];

                            disco_pino[aux] = 2;

                        }

                    //disco solto fora dos pinos, volta pra origem
                    }else{

                            DP[0] = pinos_posicao[disco_pino[aux]][0] - DT[0]/2;
                            DP[1] = empilhamento[disco_pino[aux]][9] - DT[1];

                            empilhamento[disco_pino[aux]][0]++;
                            empilhamento[disco_pino[aux]][empilhamento[disco_pino[aux]][0]] = aux;
                            empilhamento[disco_pino[aux]][9] -= DT[1];

                    }

                disco_solto = 0;
                movimentos++;

                }

            }

            //GANHOU O JOGO
            if(empilhamento[2][0] == quant_discos && movimentos <= mov_minimo + 10){

                strcpy(resultado, "GANHOU");
                pontuacao = (10 - (movimentos - mov_minimo)) * 10;

                exit_screen = TRUE;
                screen_state = 6;

            }

            //PERDEU O JOGO
            if(movimentos >= mov_minimo + 10 && empilhamento[2][0] != quant_discos){

                strcpy(resultado, "PERDEU");
                pontuacao = 0;

                exit_screen = TRUE;
                screen_state = 6;

            }


            //DRAW

            ///LATERAL
            //RETÂNGULO DE FUNDO
            rectfill(buffer, 0, 0, 200, 600, makecol(128,64,64));

            //BOTÃO DE "REINICIAR"
              //efeito highlight
            if(mouse_x > 40 && mouse_x < 40 + text_length(agentorange20, "Reiniciar")
              && mouse_y > 40 && mouse_y < 40 + text_height(agentorange20)){

                  ellipsefill(buffer, 100, 50, 85, 35, makecol(0,0,0));

            }
            ellipsefill(buffer, 100, 50, 80, 30, makecol(128,0,0));
            textout_ex(buffer, agentorange20, "Reiniciar", 40, 40, makecol(204,204,0), -1);

            //Nº DE MOVIMENTOS
            textout_ex(buffer, agentorange15, "N de movimentos", 5, 150, makecol(204,204,0), -1);
            rect(buffer, 30, 180, 160, 250, makecol(128,0,0));
            if(movimentos < 10){
                textprintf_ex(buffer, skater50, 90, 190, makecol(128,0,0), -1, "%d", movimentos);
            }else if(movimentos < 100){
                textprintf_ex(buffer, skater50, 80, 190, makecol(128,0,0), -1, "%d", movimentos);
            }else{
                textprintf_ex(buffer, skater50, 70, 190, makecol(128,0,0), -1, "%d", movimentos);
            }

            //MÍNIMO DE MOVIMENTOS
            textout_ex(buffer, agentorange15, "Minimo de", 40, 320, makecol(204,204,0), -1);
            textout_ex(buffer, agentorange15, "movimentos:", 30, 340, makecol(204,204,0), -1);
            rect(buffer, 30, 370, 160, 440, makecol(128,0,0));
            if(mov_minimo < 10){
                textprintf_ex(buffer, skater50, 90, 380, makecol(128,0,0), -1, "%d", mov_minimo);
            }else if(mov_minimo < 100){
                textprintf_ex(buffer, skater50, 80, 380, makecol(128,0,0), -1, "%d", mov_minimo);
            }else{
                textprintf_ex(buffer, skater50, 70, 380, makecol(128,0,0), -1, "%d", mov_minimo);
            }

            //BOTÃO DE "MENU"
            rectfill(buffer, 60, 510, 140, 540, makecol(128,0,0));
            if(mouse_x > 75 && mouse_x < 75 + text_length(agentorange15, "MENU")
              && mouse_y > 520 && mouse_y < 520 + text_height(agentorange15)){

                  rect(buffer, 60, 510, 140, 540, makecol(0,0,0));

            }
            textout_ex(buffer, agentorange15, "MENU", 75, 520, makecol(204,204,0), -1);

            //RETÂNGULO DA BASE
            rectfill(buffer, 200, 500, 800, 600, makecol(128,128,64));

            ///DESENHO DOS BITMAPS INSTALADOS
            //PINOS
            draw_sprite(buffer, pinos, 212, 106);
            //DISCOS
            //garantir que o disco solto seja desenhado por cima dos outros
            for(i = quant_discos-1; i >= 0; i--){

                if(i != disco_solto - 1)
                    draw_sprite(buffer, disco[i], discos_posicao[i][0], discos_posicao[i][1]);

            }

            if(disco_solto != 0){

                i = disco_solto - 1;
                draw_sprite(buffer, disco[i], discos_posicao[i][0], discos_posicao[i][1]);

            }

            draw_sprite(buffer, cursor, mouse_x-6, mouse_y);
            draw_sprite(screen, buffer, 0, 0);

            clear_to_color(buffer, makecol(221,111,0));

        }
    }

  ///FINALIZACAO
  destroy_font(agentorange15);
  destroy_font(agentorange20);
  destroy_font(skater50);
  destroy_bitmap(buffer);
  destroy_bitmap(cursor);
  destroy_bitmap(pinos);
  for(i = 0; i < 8; i++){
      destroy_bitmap(disco[i]);
  }

}

//TELA DE AJUDA
void ajuda(){

    int exit_screen = FALSE;

    ///FONTS
    FONT* skater20 = load_font("fontes/fonteSGR20.pcx", NULL, NULL);
    FONT* skater30 = load_font("fontes/fonteSGR30.pcx", NULL, NULL);
    FONT* sketch40 = load_font("fontes/fonteSM40.pcx", NULL, NULL);

    ///BITMAPS
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);

    ///GAME LOOP
    while(!exit_program && !exit_screen)
    {

        while(timer > 0 && !exit_program && !exit_screen)
        {

        //INPUT
        if(key[KEY_ESC])
        fecha_programa();

        //UPDATE
        if(key[KEY_ENTER] || key[KEY_ENTER_PAD]){
            exit_screen = TRUE;
            screen_state = 1;
        }

        //DRAW
        textout_centre_ex(buffer, sketch40, "OBJETIVO DO JOGO:", SCREEN_W/2, 100, makecol(204,204,0), -1);

        textout_centre_ex(buffer, skater20, "O problema consiste em passar todos os discos do primeiro pino para o ultimo,", SCREEN_W/2, 200, makecol(128,0,0), -1);
        textout_centre_ex(buffer, skater20, "usando o pino do meio como auxiliar, de maneira que um disco maior nunca fique", SCREEN_W/2, 220, makecol(128,0,0), -1);
        textout_centre_ex(buffer, skater20, "em cima de outro menor em nenhuma situacao. Sendo assim, ganha o jogo quem", SCREEN_W/2, 240, makecol(128,0,0), -1);
        textout_centre_ex(buffer, skater20, "consegue colocar todos os discos no ultimo pino em ordem crescente de diametro.", SCREEN_W/2, 260, makecol(128,0,0), -1);
        textout_centre_ex(buffer, skater20, "E tenha cuidado com o numero maximo de movimentos permitidos. Que sera ate 10 movimentos", SCREEN_W/2, 280, makecol(128,0,0), -1);
        textout_centre_ex(buffer, skater20, "do minimo mostrado, variando sua pontuacao de acordo com a quantidade ultrapassada.", SCREEN_W/2, 300, makecol(128,0,0), -1);
        textout_centre_ex(buffer, skater20, "O numero de discos pode variar com o minimo de tres e o maximo de oito.", SCREEN_W/2, 320, makecol(128,0,0), -1);

        line(buffer, 80, 430, 400, 430, makecol(128,0,0));
        textout_ex(buffer, skater30, "Aperte 'enter' para voltar.", 80, 450, makecol(128,0,0), -1);


        draw_sprite(screen, buffer, 0, 0);

        clear_to_color(buffer, makecol(221,111,0));

        }

    }

    ///FINALIZACAO
    destroy_font(skater20);
    destroy_font(skater30);
    destroy_font(sketch40);
    destroy_bitmap(buffer);

}

//TELA AUXILIAR
//tela utilizada para auxiliar o reinício do jogo
//para o plano de fundo não escurecer
void auxiliar(){

    int exit_screen = FALSE;

    ///BITMAP
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* tela[6] = {
                        load_bitmap("imagens/tela3.BMP", NULL),
                        load_bitmap("imagens/tela4.BMP", NULL),
                        load_bitmap("imagens/tela5.BMP", NULL),
                        load_bitmap("imagens/tela6.BMP", NULL),
                        load_bitmap("imagens/tela7.BMP", NULL),
                        load_bitmap("imagens/tela8.BMP", NULL)
                      };

    ///VARIÁVEIS
    int i;

    ///GAME LOOP
    while(!exit_program && !exit_screen)
    {

        while(timer > 0 && !exit_program && !exit_screen)
        {

        //INPUT
        if(key[KEY_ESC])
        fecha_programa();

        //UPDATE
        exit_screen = TRUE;
        screen_state = 3;

        //DRAW
        draw_sprite(buffer, tela[quant_discos - 3], 0, 0);
        draw_sprite(screen, buffer, 0, 0);

        }
    }

    ///FINALIZACAO
    destroy_bitmap(buffer);
    for(i = 0; i < 6; i++){
      destroy_bitmap(tela[i]);
    }

}

//FIM DO JOGO
void fim(){

    int exit_screen = FALSE;

    ///FONTS
    FONT* sketch30 = load_font("fontes/fonteSM30.pcx", NULL, NULL);
    FONT* sketch40 = load_font("fontes/fonteSM40.pcx", NULL, NULL);

    ///BITMAPS
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);

    ///GAME LOOP
    while(!exit_program && !exit_screen)
    {

        while(timer > 0 && !exit_program && !exit_screen)
        {

        //INPUT
        if(key[KEY_ESC])
        fecha_programa();

        //UPDATE
        if(key[KEY_ENTER] || key[KEY_ENTER_PAD]){

            exit_screen = TRUE;
            screen_state = 1;

        }

        //DRAW
        textprintf_centre_ex(buffer, sketch40, SCREEN_W/2, 250, makecol(204,204,0), -1, "VOCE %s O JOGO!!", resultado);
        textprintf_centre_ex(buffer, sketch30, SCREEN_W/2, 300, makecol(204,204,0), -1, "Pontuacao: %d", pontuacao);
        textout_centre_ex(buffer, sketch30, "APERTE 'ENTER' PARA VOLTAR.", SCREEN_W/2, 350, makecol(204,204,0), -1);

        draw_sprite(screen, buffer, 0, 0);
        clear_to_color(buffer, makecol(221,111,0));
        }

    }

    ///FINALIZACAO
    destroy_font(sketch30);
    destroy_font(sketch40);
    destroy_bitmap(buffer);

}

int main()
{

  init();

  while(!exit_program)
  {

     if(screen_state == 1)
        mainmenu();

     else if(screen_state == 2)
        escolha_nivel();

     else if(screen_state == 3)
        jogo();

     else if(screen_state == 4)
        ajuda();

     else if(screen_state == 5)
        auxiliar();

     else if(screen_state == 6)
        fim();

  }

  return 0;

}
END_OF_MAIN();
