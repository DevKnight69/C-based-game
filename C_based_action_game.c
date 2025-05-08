#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>

typedef struct {
    char name[20];
    int attack_power;
    int health;

    void (*attack)(void* self, void* target);
    void (*defend)(void* self, int damage);
    void (*special_atack)(void* self, void* target);
} Character;

typedef struct {
    Character base;
    int rage; //savaşçının özel atağı
} Warrior;

void warrior_attack(void* self, void* target) {
    Warrior* warrior = (Warrior*)self;
    Character* enemy = (Character*)target;
    printf("%s SALDIRIYOR (%d hasar!)\n", warrior->base.name, enemy->name, warrior->base.attack);
    enemy->defend(enemy, warrior->base.attack_power);
}

void warrior_defend(void* self, int damage) {
    Warrior* warrior = (Warrior*)self;
    warrior->base.health -= damage;
    printf("%s HASAR ALINDI! (kalan can %d.)\n", warrior->base.name, damage, warrior->base.health);
}

void special_atack(void* self, void* target) {
    Warrior* w = (Warrior*)self;
    Character* defender = (Character*)target;

    if (w->rage >= 20){
        printf("%s ÖZEL SALDIRI YAPIYOR (%d hasar!)\n", w->base.name, defender->name, w->rage);
        defender->defend(defender, w->rage);
        w->rage = 0;
    } else {
        printf("%s ÖZEL SALDIRI İÇİN YETERLİ ÖFKE YOK!\n", w->base.name);
    }
}

Warrior* new_warrior(const char* name){
    Warrior* w = malloc(sizeof(Warrior));
    strcpy(w->base.name, name);
    w ->base.health =  100;
    w ->base.attack_power = 20;
    w ->base.attack = warrior_attack;
    w ->base.defend = warrior_defend;
    w ->base.special_atack = special_atack;
    w->rage = 20;
    return w;
}

typedef struct {
    Character base;
    int supernova; //büyücünün özel atağı
} Wizard;

void wizard_attack(void* self, void* target) {
    Wizard* wizard = (Wizard*)self;
    Character* enemy = (Character*)target;
    printf("%s SALDIRIYOR (%d hasar!)\n", wizard->base.name, enemy->name, wizard->base.attack);
    enemy->defend(enemy, wizard->base.attack_power);
}

void wizard_defend(void* self, int damage) {
    Wizard* wizard = (Wizard*)self;
    wizard->base.health -= damage;
    printf("%s HASAR ALINDI! (kalan can %d.)\n", wizard->base.name, damage, wizard->base.health);
}

void wizard_special_attack(void* self, void* target) {
    Wizard* wiz = (Wizard*)self;
    Character* defender = (Character*)target;

    if (wiz->supernova >= 20){
        printf("%s ÖZEL SALDIRI YAPIYOR (%d hasar!)\n", wiz->base.name, defender->name, wiz->supernova);
        defender->defend(defender, wiz->supernova);
        wiz->supernova = 0;
    } else {
        printf("%s ÖZEL SALDIRI İÇİN YETERLİ MANAYA SAHİP DEĞİL!\n", wiz->base.name);
    }
}

Wizard* new_wizard(const char* name){
    Wizard* wiz = malloc(sizeof(Wizard));
    strcpy(wiz->base.name, name);
    wiz ->base.health = 100;
    wiz ->base.attack_power = 10;
    wiz ->base.attack = wizard_attack;
    wiz ->base.defend = wizard_defend;
    wiz ->base.special_atack = wizard_special_attack;
    wiz->supernova = 20;
    return wiz;
}

int main(){
    srand(time(NULL));
    int choice;
    Character* player = NULL;
    Character* enemy = NULL;

    printf("Karakterinizi Seçiniz:\n");
    printf("1. Savaşçı\n");
    printf("2. Büyücü\n");
    printf("Seçiminiz: ");
    scanf("%d", &choice);

    if (choice == 1) 
        player = (Character*)new_warrior("Savaşçı");

    else if (choice == 2)
        player = (Character*)new_wizard("Büyücü");

    else {
        printf("Geçersiz seçim!\n");
        return 1;
    }
    
    int enemy_type = rand() % 2;
    if (enemy_type == 0) 
        enemy = (Character*)new_warrior("Düşman Savaşçı");
    else{ 
        enemy = (Character*)new_wizard("Düşman Büyücü");

        printf("\n === SAVAŞ BAŞLIYOOOOOOR === \n\n");
    }

    getchar();
    return 0;
}






