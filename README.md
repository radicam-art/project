# Hardware Watcher
#### Video Demo:  <https://youtu.be/DXKCnuSUKRI>
#### Description:README

	Hardware Watcher July 28th 2021
	-------------------------------

Welcome to the Hardware Watcher readme! 
This program is wrote by C/C++.

Type "help" or "!help" on my program to know
 how to use this program!

To get more infomation, please visit https://youtu.be/DXKCnuSUKRI/

Sincerely,
kenshin ueda from Japan

==================================================================
### How this program files works

logFiles: save CPU/Memory/GPU data as csv file.
duck: duck AA text file for secret commands.
finalproject.cpp: Sorce code c/c++.
finalproject.exe: Need admin access to show disk infomation.
		  This exe-file is for watch Hardware Information.
		  
		  [Commands] 

		  mem: Display available memory
 		  mem-file: Display available memory and record to log file
 		  cpu: Total processor usage
 		  cpu-file: Total processor usage and record to log file
 		  list: Display all active tasks
 		  gpu-nvidia-simple: Display simple GPU info
 		  gpu-nvidia-simple-file: Save GPU info to log file
 		  disk: Display free and usage disk bytes (Admin access is required)
		  cs50/duck/coder/hi/hello/now: Secret commands
		  
		  cs50/duck: display some secret duck! Have fun :)
		  coder: display coder infomation
		  hi/hello: return "Hello!"
		  now: display time stamp to someone who lazy to know now time...(me)
		  
 		  close/end/bye/good bye: Close this program with saying "bye!"

finalproject.exe.manifest: Assembly manifest-file to get Admin access.
nvidia-smi.exe: Nvidia's software to get GPU infomation.
README: This text-file. And this text file describe some secret commands!
        If you type "cs50" or "duck", you can find duck(or maybe chick) in your
         window! This is awesome I thought!

===================================================================
### What can you do by this program?

You can watch your Hardware resourses and know how it works even when you in games or something!
Write on log-files is now officialy provide you to watch CPU/Memory/GPU information while you playing
games and watch it later!!

===================================================================

### version Infomation!
ver.1.0 2021.7

### Japanese info
このプログラムはハードウェアの使用状況をタスクマネージャー等のように並行的に表示することに加えて、その情報を記録し、また
これらの情報を後から確認することを可能にするためのソフトウェアです。タスクマネージャーとうでのリアルタイムでの使用状況共有では
分からなかったボトルネックを見つけ出して、これによってゲーム等のFPS値の上昇や、ソフトウェア等の動作状況改善に必要な
ハードウェア面での改善部分を明らかにできます。
言語はC/C++を使用し、コマンドラインプログラムとして機能します。ディスクの状況確認に必要なため、管理者権限を必要とします。
