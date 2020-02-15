@echo off
bmp2tile.exe .\gfx\SegaMasterSystemTitleScreen.png -savetiles .\bank1\backgroundtiles.psgcompr -mirror -removedupes -savepalette .\bank1\backgroundpalette.bin -savetilemap .\bank1\backgroundtilemap.bin -exit
bmp2tile.exe .\gfx\spyvsspyspritesheet.png -nomirror -noremovedupes -savetiles .\bank1\spritetiles.psgcompr -palsms -savepalette .\bank1\spritepalette.bin -exit
folder2c bank1 bank1
sdcc -c -mz80 --peep-file peep-rules.txt bank1.c
sdcc -c -mz80 --peep-file peep-rules.txt main.c
sdcc -o output.ihx -mz80 --no-std-crt0 --data-loc 0xC000 crt0_sms.rel main.rel bank1.rel SMSlib.lib PSGlib.rel

ihx2sms output.ihx output.sms
output.sms