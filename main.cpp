#include<allegro5/allegro5.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include <stdio.h>

// Definindo configuracoes do mapa
#define TAMBLOCO 32
#define WMAPA 50
#define HMAPA 25
#define SCREENWIDTH TAMBLOCO*WMAPA
#define SCREENHEIGHT TAMBLOCO*HMAPA

#define CHAO_PEDRA 2
#define CHAO_AREIA 3
#define CHAO_TERRA 4

// Atributos do player1.png
float frame1 = 0.f;
int frameAtualY1 = 0; // Posicao referente ao sprite
int posX1 = 3 * TAMBLOCO;
int posY1 = 12 * TAMBLOCO;

// Atributos do player2.png
float frame2 = 0.f;
int frameAtualY2 = 0; // Posicao referente ao sprite
int posX2 = 5 * TAMBLOCO;  
int posY2 = 12 * TAMBLOCO; 

// Teclas de movimentacao
enum KEYS { UP, DOWN, LEFT, RIGHT };
enum KEYS2 { W, S, A, D };

// Variaveis para coletar itens
bool item_seringa_coletado = false;
bool item_kit_coletado = false;
bool item_xarope_coletado = false;
bool item_lenco_coletado = false;

// Atribuindo as imagens no mapa
int mapa[HMAPA][WMAPA] = {
    {1, 1, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {1, 1, 0, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0,},
    {1, 1, 0, 3, 3, 3, 0, 3, 3, 3, 3, 0, 0, 0, 0, 6, 2, 2, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {1, 1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 0, 0, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0,},
    {1, 1, 0, 0, 0, 7, 0, 0, 0, 8, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {1, 1, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 2, 2, 2, 0, 0, 0, 4, 4, 4, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {1, 1, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 10, 0, 7, 9, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 0, 4, 4, 4, 8, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {1, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0,},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 0, 0, 0, 0, 0, 10, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 0,},
    {1, 1, 0, 0, 0, 0, 11, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0,},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0,},
    {1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 0, 0,},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 9, 4, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0,},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 3, 3, 3, 3, 3, 3, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0,},
    {1, 1, 0, 0, 0, 7, 0, 0, 0, 0, 4, 4, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 4, 4,},
    {1, 1, 0, 0, 0, 0, 0, 0, 4, 4, 4, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 0, 11, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 4,},
    {1, 1, 3, 0, 0, 0, 8, 0, 4, 0, 0, 0, 0, 7, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,},
    {1, 1, 3, 3, 0, 0, 10, 4, 4, 4, 4, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 11, 0, 7, 0, 0, 4, 4,},
    {1, 1, 3, 3, 3, 0, 0, 4, 0, 0, 4, 0, 0, 0, 0, 0, 4, 0, 0, 4, 4, 4, 0, 0, 0, 4, 4, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 4, 4, 4, 0, 0, 0, 0, 0, 7, 0, 4, 4, 0,},
    {1, 1, 3, 3, 0, 0, 4, 4, 0, 0, 4, 4, 4, 0, 4, 4, 4, 0, 0, 0, 0, 4, 4, 0, 0, 4, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 4, 4, 0, 4, 4, 4, 4, 4, 4, 0, 4, 4, 0, 0,},
    {1, 1, 3, 3, 3, 3, 4, 0, 0, 0, 0, 0, 4, 0, 4, 0, 0, 0, 0, 7, 7, 0, 4, 4, 4, 4, 0, 0, 0, 8, 0, 4, 0, 0, 0, 0, 4, 0, 0, 10, 0, 0, 0, 0, 4, 4, 3, 0, 0, 3,},
    {1, 1, 3, 3, 11, 4, 4, 0, 0, 0, 0, 0, 4, 4, 4, 0, 0, 0, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 4, 4, 4, 0, 0, 0, 0, 0, 0, 10, 0, 3, 3, 3, 0, 3,},
    {1, 1, 3, 3, 0, 4, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 10, 0, 0, 0, 4, 12, 4, 4, 0, 0, 4, 0, 11, 0, 0, 7, 7, 0, 0, 0, 0, 0, 3, 3, 3, 3,},
    {1, 1, 3, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 3, 3, 13,},
};

// Atualizando a posicao no sprite
void atualizarSprite(float& sprite) {
    sprite += 0.3f;
    if (sprite > 3) {
        sprite -= 3;
    }
}

ALLEGRO_BITMAP* grama = NULL;
ALLEGRO_BITMAP* grama_alta = NULL;
ALLEGRO_BITMAP* chao_pedra = NULL;
ALLEGRO_BITMAP* chao_areia = NULL;
ALLEGRO_BITMAP* chao_terra = NULL;
ALLEGRO_BITMAP* planta1 = NULL;
ALLEGRO_BITMAP* planta2 = NULL;
ALLEGRO_BITMAP* planta3 = NULL;
ALLEGRO_BITMAP* buraco = NULL;
ALLEGRO_BITMAP* morro = NULL;
ALLEGRO_BITMAP* m_seringa = NULL;
ALLEGRO_BITMAP* m_kit = NULL;
ALLEGRO_BITMAP* m_xarope = NULL;
ALLEGRO_BITMAP* m_lenco = NULL;

// Funcao para desenhar o mapa com base na matriz
void desenharMapa() {
    for (int i = 0; i < HMAPA; i++) {
        for (int j = 0; j < WMAPA; j++) {
            int dx = j * TAMBLOCO;
            int dy = i * TAMBLOCO;

            printf("mapa[%d][%d] = %d\n", i, j, mapa[i][j]); // linha para debug

            // Desenhar o terreno
            switch (mapa[i][j]) {
            case 0:
                al_draw_bitmap(grama, dx, dy, 0);
                break;

            case 1:
                al_draw_bitmap(grama_alta, dx, dy, 0);
                break;

            case 2:
                al_draw_bitmap(chao_pedra, dx, dy, 0);
                break;

            case 3:
                al_draw_bitmap(chao_areia, dx, dy, 0);
                break;

            case 4:
                al_draw_bitmap(chao_terra, dx, dy, 0);
                break;

            default:
                al_draw_bitmap(grama, dx, dy, 0);
                break;
            }

            // Desenhar os itens por cima do terreno
            switch (mapa[i][j]) {
            case 6:
                al_draw_bitmap(chao_pedra, dx, dy, 0);
                al_draw_bitmap(m_seringa, dx, dy, 0);
                break;

            case 7:
                al_draw_bitmap(planta1, dx, dy, 0);
                break;

            case 8:
                al_draw_bitmap(buraco, dx, dy, 0);
                break;

            case 9:
                al_draw_bitmap(morro, dx, dy, 0);
                break;

            case 10:
                al_draw_bitmap(planta2, dx, dy, 0);
                break;

            case 11:
                al_draw_bitmap(planta3, dx, dy, 0);
                break;

            case 12:
                al_draw_bitmap(chao_terra, dx, dy, 0);
                al_draw_bitmap(m_kit, dx, dy, 0);
                break;

            case 13:
                al_draw_bitmap(chao_areia, dx, dy, 0);
                al_draw_bitmap(m_xarope, dx, dy, 0);
                break;

            case 14:
                al_draw_bitmap(chao_terra, dx, dy, 0);
                al_draw_bitmap(m_lenco, dx, dy, 0);
                break;
            }
        }
    }
}

// FUncao de movimentacao do player1
void movimentacaoPlayer1(int direcao) {
    int newPosX1 = posX1;
    int newPosY1 = posY1;
    int newFrameY1 = frameAtualY1;

    switch (direcao) {
    case UP:
        newPosY1 -= 8;
        newFrameY1 = 0;
        break;
    case DOWN:
        newPosY1 += 8;
        newFrameY1 = 72;
        break;
    case LEFT:
        newPosX1 -= 8;
        newFrameY1 = 108;
        break;
    case RIGHT:
        newPosX1 += 8;
        newFrameY1 = 36;
        break;
    }

    // Colisão com itens específicos, o lugar do item sera atualizado para o chao
    int mapValue = mapa[newPosY1 / TAMBLOCO][newPosX1 / TAMBLOCO];
    switch (mapValue) {
    case 6:
        item_seringa_coletado = true;
        mapa[newPosY1 / TAMBLOCO][newPosX1 / TAMBLOCO] = 2;
        break;

    case 12:
        item_kit_coletado = true;
        mapa[newPosY1 / TAMBLOCO][newPosX1 / TAMBLOCO] = 4;
        break;

    case 13:
        item_xarope_coletado = true;
        mapa[newPosY1 / TAMBLOCO][newPosX1 / TAMBLOCO] = 3;
        break;

    case 14:
        item_lenco_coletado = true;
        mapa[newPosY1 / TAMBLOCO][newPosX1 / TAMBLOCO] = 4;
        break;
    }

    if (newPosY1 >= 0 && newPosY1 <= SCREENHEIGHT - TAMBLOCO &&
        newPosX1 >= 0 && newPosX1 <= SCREENWIDTH - TAMBLOCO &&
        (mapa[newPosY1 / TAMBLOCO][newPosX1 / TAMBLOCO] == CHAO_PEDRA ||
            mapa[newPosY1 / TAMBLOCO][newPosX1 / TAMBLOCO] == CHAO_AREIA ||
            mapa[newPosY1 / TAMBLOCO][newPosX1 / TAMBLOCO] == CHAO_TERRA)) {

        posY1 = newPosY1;
        posX1 = newPosX1;
        frameAtualY1 = newFrameY1;
    }
}

// Funcao de movimentacao do player2
void movimentacaoPlayer2(int direction) {
    int newPosX2 = posX2;
    int newPosY2 = posY2;
    int newFrameY2 = frameAtualY2;

    switch (direction) {
    case W:
        newPosY2 -= 8;
        newFrameY2 = 0;
        break;
    case S:
        newPosY2 += 8;
        newFrameY2 = 72;
        break;
    case A:
        newPosX2 -= 8;
        newFrameY2 = 108;
        break;
    case D:
        newPosX2 += 8;
        newFrameY2 = 36;
        break;
    }

    // Colisão com itens específicos, o lugar do item sera atualizado para o chao
    int mapValue = mapa[newPosY2 / TAMBLOCO][newPosX2 / TAMBLOCO];
    switch (mapValue) {
    case 6:
        item_seringa_coletado = true;
        mapa[newPosY2 / TAMBLOCO][newPosX2 / TAMBLOCO] = 2;
        break;
    case 12:
        item_kit_coletado = true;
        mapa[newPosY2 / TAMBLOCO][newPosX2 / TAMBLOCO] = 4;
        break;
    case 13:
        item_xarope_coletado = true;
        mapa[newPosY2 / TAMBLOCO][newPosX2 / TAMBLOCO] = 3;
        break;
    case 14:
        item_lenco_coletado = true;
        mapa[newPosY2 / TAMBLOCO][newPosX2 / TAMBLOCO] = 4;
        break;
    }

    if (newPosY2 >= 0 && newPosY2 <= SCREENHEIGHT - TAMBLOCO &&
        newPosX2 >= 0 && newPosX2 <= SCREENWIDTH - TAMBLOCO &&
        (mapa[newPosY2 / TAMBLOCO][newPosX2 / TAMBLOCO] == CHAO_PEDRA ||
            mapa[newPosY2 / TAMBLOCO][newPosX2 / TAMBLOCO] == CHAO_AREIA ||
            mapa[newPosY2 / TAMBLOCO][newPosX2 / TAMBLOCO] == CHAO_TERRA)) {

        posY2 = newPosY2;
        posX2 = newPosX2;
        frameAtualY2 = newFrameY2;
    }
}

int main() {
    ALLEGRO_DISPLAY* display;

    const float FPS = 30.0;
    bool done = false;
    bool redesenha = true;

    // Se as teclas estao pressionadas
    bool keys[4] = { false, false, false, false };
    bool keys2[4] = { false, false, false, false };

    al_init();
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();

    display = al_create_display(SCREENWIDTH, SCREENHEIGHT);
    al_set_window_position(display, 200, 200);

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // Sprites do players
    ALLEGRO_BITMAP* player1 = al_load_bitmap("player1.png");
    ALLEGRO_BITMAP* player2 = al_load_bitmap("player2.png");

    // Imagens usadas para o mapa
    grama = al_load_bitmap("grama.png");
    grama_alta = al_load_bitmap("grama-alta.png");
    chao_pedra = al_load_bitmap("chao-pedra.png");
    chao_areia = al_load_bitmap("areia.png");
    chao_terra = al_load_bitmap("terra.png");
    planta1 = al_load_bitmap("planta1.png");
    planta2 = al_load_bitmap("planta2.png");
    planta3 = al_load_bitmap("planta3.png");
    buraco = al_load_bitmap("buraco.png");
    morro = al_load_bitmap("morro.png");
    m_seringa = al_load_bitmap("m_seringa.png");
    m_kit = al_load_bitmap("m_kit.png");
    m_xarope = al_load_bitmap("m_xarope.png");
    m_lenco = al_load_bitmap("m_lenco.png");

    al_start_timer(timer);

    while (!done) {
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);
        ALLEGRO_EVENT_TYPE tipoEvento = events.type;

        atualizarSprite(frame1);
        atualizarSprite(frame2);

        // Identificando os eventos ocorridos
        if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        // Teclas pressionadas do primeiro jogador - player1
        else if (events.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (events.keyboard.keycode) {
                // Jogador 1
            case ALLEGRO_KEY_UP:
                keys[UP] = true;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = true;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = true;
                break;
            }
        }
        // Se as teclas pressionadas foram soltas - player1
        else if (events.type == ALLEGRO_EVENT_KEY_UP) {
            switch (events.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                keys[UP] = false;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = false;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = false;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = false;
                break;
            }
        }

        // Teclas pressionadas do segundo jogador - player2
        if (events.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (events.keyboard.keycode) {
            case ALLEGRO_KEY_W:
                keys2[W] = true;
                break;
            case ALLEGRO_KEY_S:
                keys2[S] = true;
                break;
            case ALLEGRO_KEY_A:
                keys2[A] = true;
                break;
            case ALLEGRO_KEY_D:
                keys2[D] = true;
                break;
            }
        }

        // Se as teclas pressionadas foram soltas - player2
        else if (events.type == ALLEGRO_EVENT_KEY_UP) {
            switch (events.keyboard.keycode) {
            case ALLEGRO_KEY_W:
                keys2[W] = false;
                break;
            case ALLEGRO_KEY_S:
                keys2[S] = false;
                break;
            case ALLEGRO_KEY_A:
                keys2[A] = false;
                break;
            case ALLEGRO_KEY_D:
                keys2[D] = false;
                break;
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            }
        }

        // Realizando a movimentacao do player1 
        if (keys[UP]) {
            movimentacaoPlayer1(  UP);
        }

        if (keys[DOWN]) {
            movimentacaoPlayer1(  DOWN);
        }

        if (keys[LEFT]) {
            movimentacaoPlayer1(  LEFT);
        }

        if (keys[RIGHT]) {
            movimentacaoPlayer1(  RIGHT);
        }

        // Realizando a movimentacao do player2 
        if (keys2[W]) {
            movimentacaoPlayer2(  W);
        }

        if (keys2[S]) {
            movimentacaoPlayer2(  S);
        }

        if (keys2[A]) {
            movimentacaoPlayer2(  A);
        }

        if (keys2[D]) {
            movimentacaoPlayer2(  D);
        }

        // Verificando se as teclas foram pressionadas, caso sim sera necessario redesenhar o mapa
        if (keys[UP] || keys[DOWN] || keys[LEFT] || keys[RIGHT] ||
            keys2[W] || keys2[S] || keys2[A] || keys2[D]) {
            redesenha = true;
        }

        // Se for necessario
        if (redesenha) {
            desenharMapa();

            al_draw_bitmap_region(player1, (int)frame1 * 32, frameAtualY1, 32, 32, posX1, posY1, 0);
            al_draw_bitmap_region(player2, (int)frame2 * 32, frameAtualY2, 32, 32, posX2, posY2, 0);

            al_flip_display();
            redesenha = false;
        }

    }

    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    al_destroy_bitmap(grama);
    al_destroy_bitmap(grama_alta);
    al_destroy_bitmap(chao_pedra);
    al_destroy_bitmap(chao_areia);
    al_destroy_bitmap(planta1);
    al_destroy_bitmap(planta2);
    al_destroy_bitmap(planta3);
    al_destroy_bitmap(buraco);
    al_destroy_bitmap(morro);
    al_destroy_bitmap(m_seringa);
    al_destroy_bitmap(m_kit);
    al_destroy_bitmap(m_xarope);
    al_destroy_bitmap(m_lenco);
    al_destroy_bitmap(player1);
    al_destroy_bitmap(player2);

    return 0;
}