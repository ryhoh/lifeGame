#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define HEIGHT 50
#define WIDTH 128

void initialize(int world[][WIDTH+2]);
void update(int world[][WIDTH+2]);
void make(int world[][WIDTH+2], int size);
void makeGlyder(int world[][WIDTH+2]);
void printWorld(int world[][WIDTH+2]);

// 2次元配列worldで管理
// 周りを0の要素で囲むことでセグフォを容易に回避

int main(){
    int world[HEIGHT+2][WIDTH+2];
    initialize(world);
    printWorld(world);
    int count = 0;
    
    while(1){
        //sleep(1);
        usleep(100000);
        update(world);
        // 普通に更新していくと動きがなくなって面白くないので、左上で新たに生成する
        if(count == 20){
            //make(world, 24);
            makeGlyder(world);
            count = 0;
        } else
            count++;
        
        printWorld(world);
    }
    
    return 0;
}

// 生存なら1, そうでなければ0
void initialize(int world[][WIDTH+2]){
    // 外枠を0クリアしたいので一旦全部0に
    for(int i = 0; i < HEIGHT+2; i++)
        for(int j = 0; j < WIDTH+2; j++)
            world[i][j] = 0;
    
    // データを内側にだけ入れる
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            world[i+1][j+1] = ((rand() % 10) < 2) ? 1 : 0;   // 乱数を使って生成
        }
    }
}

void update(int world[][WIDTH+2]){
    int old[HEIGHT+2][WIDTH+2];
    int count;
    
    // 退避
    for(int i = 0; i < HEIGHT+2; i++){
        for(int j = 0; j < WIDTH+2; j++){
            old[i][j] = world[i][j];
        }
    }
    
    // 更新
    for(int i = 1; i < HEIGHT+1; i++){
        for(int j = 1; j < WIDTH+1; j++){
            count = 0;
            
            // 外枠が0で作られているので端でもおかまいなし
            for(int m = i-1; m < i+2; m++){
                for(int n = j-1; n < j+2; n++){
                    if(m == i && n == j)
                        continue;
                    else
                        count += old[m][n];
                }
            }
            
            // 判定
            if(old[i][j] == 0){
                // 現在死んでいる
                if(count == 3){
                    // 誕生
                    world[i][j] = 1;
                }
            } else {
                // 現在生きている
                if(count <= 1){
                    // 過疎
                    world[i][j] = 0;
                } else if(4 <= count){
                    // 過密
                    world[i][j] = 0;
                }   // 生存ならそのまま
            }
        }
    }
}

void make(int world[][WIDTH+2], int size){
    for(int i = 1; i < size+1; i++){
        for(int j = 1; j < size+1; j++){
            world[i][j] = ((rand() % 10) < 2) ? 1 : 0;   // 乱数を使って生成
        }
    }
}

void makeGlyder(int world[][WIDTH+2]){
    for(int i = 1; i < 4; i++){
        for(int j = 1; j < 4; j++){
            world[i][j] = 0;
        }
    }
    
    for(int j = 1; j < 4; j++)
        world[3][j] = 1;
    world[2][3] = world[1][2] = 1;
}

void printWorld(int world[][WIDTH+2]){
    system("clear");    // 画面を一旦クリア
    
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            if(world[i+1][j+1]){
                printf("■");
            } else {
                printf("□");
            }
        }
        printf("\n");
    }
    printf("\n");
}