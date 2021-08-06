//<-.h>ファイル
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//<->ファイル
#include <algorithm>
#include <cctype>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

//プロトタイプ宣言
int countWhiteSpace(int maxCol, int charLength);
void printFrontText(string c, int maxCol);
int helper();
int doCmd(string cmd);
int getCmd();
void errorM(int number);
void bye(void);

//グローバル変数
std::string cmd;

//構造体
struct name{
    char name[20] = "kenshin ueda";
    int age = 21;
    char region[10] = "Japan";
}name;

int main(void)
{
    //変数宣言
    int num = 0,maxCol = 40, maxRow = 6, col, row, count = 1;
    std::string str;
    
    //日本語を使用した際の文字化け防止
    system("chcp 65001");
    
    //先頭の説明用ボックスを表示
    for(row = 0; row < maxRow; row++){
        for(col = 0; col < maxCol; col++){
            if(col == 0 || row == 0 || row == maxRow - 1 || col == maxCol - 1){
                printf("*");
            }

            else if(row == 1 && count == 1){
                str = "This is cs50 and Final Project";
                printFrontText(str, maxCol);
                count++;
            }

            else if(row == 2 && count == 2){
                str = "Coded by Kenshin Ueda from Japan";
                printFrontText(str, maxCol);
                count++;
            }
            
            else if(row == 3 && count == 3){
                str = "\"Hardware Watcher\"";
                printFrontText(str, maxCol);
                count++;
            }

            else if(row == 4 && count == 4){
                str = "07/2021 ";
                printFrontText(str, maxCol);
                count++;
            }
        }
        printf("\n");
    }

    //コマンド入力を受け付ける
    getCmd();
 
    return 0;
}

//文の空白を整えるための関数
int countWhiteSpace(int maxCol, int charLength){
    
    int charLengthAfter = ((maxCol - charLength) / 2) - 1; 
    
    for (charLengthAfter; charLengthAfter > 0; charLengthAfter--){
        cout << " ";
    }
    
    return 0;
}

//最初の表示文を表示し、文の空白を整える関数
void printFrontText(string c, int maxCol){
    countWhiteSpace(maxCol, (int)(c.length()));
    std::cout << c;
    countWhiteSpace(maxCol, (int)(c.length()));
}

//ヘルプ表示用関数
int helper(){
    cout << "\033[36m mem:\033[m Display available memory" << endl << "\033[36m mem-file:\033[m Display available memory and record to log file" << endl << "\033[36m cpu:\033[m Total processor usage" << endl << "\033[36m cpu-file:\033[m Total processor usage and record to log file" << endl << "\033[36m list:\033[m Display all active tasks"<< endl <<
    "\033[36m gpu-nvidia-simple:\033[m Display simple GPU info" << endl << "\033[36m gpu-nvidia-simple-file:\033[m Save GPU info to log file"  << endl << 
    "\033[36m disk:\033[m Display free and usage disk bytes (Admin access is required)" << endl << "\033[36m close:\033[m Close this program" << endl;
    
    //コマンド入力受付に戻る
    getCmd();
}

//それぞれのコマンドを実行するための関数
int doCmd(string cmd){
    if(cmd == "!help" || cmd == "help"){
       //helperに値を渡す
       helper();
    }

    //メモリの情報を表示
    else if(cmd == "mem"){
        errorM(200);
        system("typeperf \"\\Memory\\Available MBytes\"");
    }
    
    //メモリの情報をlogファイルに表示
    else if(cmd == "mem-file" || cmd == "mem-files"){
        std::string times;
        int time;

        cout << "How many times do you need to record? : ";
        cin >> time;

        //int型の入力をstd::string型に変換
        std::ostringstream oss;
        oss << time;
        times = oss.str().c_str();

        //有効な入力ではない時の処理
        if(times == "0" || times == "4227112"){
            //エラーメッセージ
            errorM(100);
            
            //コマンドコンソールに残された文字列を削除
            std::cin.clear();
            getCmd();
        }
        
        //入力された数字とコマンドを連結
        else{
            string passbuff("typeperf -sc ");
            passbuff.append(times);
            passbuff.append(" -si 1 -o logFiles/memData.csv -y \"\\Memory\\Available MBytes\"");
            cout << passbuff << endl; 
        
            //std::string型からconst char*型に変換（system(const char *)であるため）
            const char *pass = passbuff.c_str();
            
            errorM(200);
            system(pass);
            getCmd();
        }
    }
    
    //CPUの情報を表示
    else if(cmd == "cpu"){
        errorM(200);
        system("typeperf \"\\processor(_total)\\% processor time\"");
    }

    //CPUの情報をlogファイルに表示
    else if(cmd == "cpu-file" || cmd == "cpu-files"){
        std::string times;
        int time;
        
        
        cout << "How many times do you need to record? : ";
        cin >> time;

        //int型の入力をstd::string型に変換
        std::ostringstream oss;
        oss << time;
        times = oss.str().c_str();

        //有効な入力ではない時の処理
        if(times == "0" || times == "4227112"){
            //エラーメッセージ
            errorM(100);
            
            //コマンドコンソールに残された文字列を削除
            std::cin.clear();
            getCmd();
        }
        
        //入力された数字とコマンドを連結
        else{
            string passbuff("typeperf -sc ");
            passbuff.append(times);
            passbuff.append(" -si 1 -o logFiles/cpuData.csv -y \"\\processor(_Total)\\% Processor Time\"");
            cout << passbuff << endl; 
        
            //std::string型からconst char*型に変換（system(const char *)であるため）
            const char *pass = passbuff.c_str();
            
            errorM(200);
            system(pass);
            getCmd();
        }
        
    }

    //稼働中のタスク一覧を表示
    else if(cmd == "list" || cmd == "lists"){
        system("tasklist");
        getCmd();
    }

    //GPUの全情報を表示
    //起動するとnvidia-smiの仕様で落ちてしまうので、保留
    else if(cmd == "gpu-nvidia"){
        char passbuff[] = "nvidia-smi";
        //同一フォルダ内にあるnvidia-smi.exeを起動
        system(passbuff);
    }

    //シンプルなGPUの情報を表示
    else if(cmd == "gpu-nvidia-simple"){
        //GPUの情報を日付、タイムスタンプ、GPU名、GPU使用率、GPUメモリ使用率、メモリ使用量、メモリ残量を表示
        char passbuff[] = "nvidia-smi \
                        --query-gpu=timestamp,name,utilization.gpu,utilization.memory,memory.used,memory.free\
                        --format=csv \
                        -l 1";
        
        errorM(200);
        //同一フォルダ内にあるnvidia-smi.exeを起動
        system(passbuff);
    }

    //シンプルなGPUの情報を表示し、logファイルに記録する
    else if(cmd == "gpu-nvidia-simple-file" || cmd == "gpu-nvidia-simple-files"){
        //GPUの情報を日付、タイムスタンプ、GPU名、GPU使用率、GPUメモリ使用率、メモリ使用量、メモリ残量を表示し、logファイルに記録する
        char passbuff[] = "nvidia-smi \
                        --query-gpu=timestamp,name,utilization.gpu,utilization.memory,memory.used,memory.free\
                        --format=csv \
                        -l 1 -f logFiles/gpuData.log";
        
        cout << "Recording GPU state\033[6m...\033[m [Ctrl+C] will stop this process." << endl;

        //同一フォルダ内にあるnvidia-smi.exeを起動
        system(passbuff);
    }

    else if(cmd == "disk" || cmd == "disks"){
        //ディスクの残容量を表示（管理者モードでのアクセスが必要）
        std::string disk;
        cout << "Which Disk do you want to check?" << endl;
        
        //残容量を確認したいディスクを入力
        cin >> disk;
        
        //受け付けた入力を小文字に変換
        transform(disk.begin(), disk.end(), disk.begin(), ::tolower);
        
        //入力された文字列とコマンドを連結
        string passbuff("fsutil volume diskfree ");
        passbuff.append(disk);
        passbuff.append(":");
        cout << passbuff << endl; 
        
        //std::string型からconst char*型に変換（system(const char *)であるため）
        const char *pass = passbuff.c_str();
        system(pass);
        getCmd();
    }

    //Secret commands
    //ひよこのAAを表示
    else if(cmd == "cs50" || cmd == "duck"){
        FILE *fp;
        char txt[2048];
        if((fp = fopen("duck.txt", "r")) != NULL){
            for(;;){
                int i = fgetc(fp);
                if(i == EOF){
                    break;
                }
                putchar(i);
            }
        }
        fclose(fp);
        getCmd();
    }

    //coderのデータ
    else if(cmd == "coder"){
        cout << endl << "name: " << name.name << endl << "age: " << name.age << " (26/7/2021)" << endl << "region: " << name.region <<endl;
        time_t t = time(NULL);
        cout << "Time stamp: " << ctime(&t) << endl;
        getCmd();
    }

    //timeStampの表示
    else if(cmd == "time" || cmd == "now"){
        time_t t = time(NULL);
        cout << "Time stamp: " << ctime(&t) << endl;
        getCmd();
    }

    //finalProjectについて
    else if(cmd == "final-project"){
        cout << "This final project is made for cs50's educational program." << endl;
        getCmd();
    }

    //挨拶
    else if(cmd == "hello" || cmd == "hi"){
        cout << "Hello!" << endl;
        getCmd();
    }

    else if(cmd == "bye" || cmd == "good bye"){
        atexit(bye);
    }

    //プログラムを終了する
    else if(cmd == "close" || cmd == "end"){
        atexit(bye);
    }

    //関係のないコマンドが入力されたときの処理
    else{
        errorM(101);
        getCmd();
    }
}

//コマンドを受け付ける関数
int getCmd(){
    cout << "\033[33m !help shows all commands.\033[m" << endl << "Command?: ";
    
    //コマンドの入力受付
    cin >> cmd;
    
    //受け付けた入力を小文字に変換
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

    //受け付けたコマンドに対して、それぞれ実行
    doCmd(cmd);
}

//エラーメッセージを表示/管理する関数
void errorM(int number){
    //不正な入力
    if(number == 100){
        cout << "Error: Only over 0 numbers can use." << endl;
    }

    //不正なコマンドの入力
    if(number == 101){
        cout << "Invailed input. Type !help will show you all command available." << endl;
    }

    //終了コマンドを表示
    if(number == 200){
        cout << "[Ctrl+C] will stop this process." << endl;
    }
}

//終了メッセージを表示する関数
void bye(void){
    //終了メッセージを表示して、文字の色の変更を防止する。
    cout << "\033[37mbye!\033[m" << endl;
    Sleep(1000);
}

/*
This was cs50 and thank you for great classes!
I used VS code for this software.
I still studying English so if their are some wrong words, plz forgive me ; ;
Thank you all of cs50 staffs! I learned a lot!
<!--       _
       .__(.)< (MEOW)
        \___)   
 ~~~~~~~~~~~~~~~~~~--> <- I found him/her on Amazon's prime video html :)
*/