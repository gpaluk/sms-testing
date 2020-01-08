@echo off
"C:\Program Files\SDCC\bin\sdcc" -c -mz80 main.c
"C:\Program Files\SDCC\bin\sdcc" -o output.ihx -mz80 --data-loc 0xC000 --no-std-crt0 crt0_sms.rel main.rel SMSlib.lib
ihx2sms output.ihx output.sms
output.sms