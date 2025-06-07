@echo off
echo === He thong Quan ly Thu vien ===
echo Dang bien dich...

if not exist scr\data mkdir scr\data

gcc -Wall -I include -o library.exe scr/main.c scr/modules/book/book.c scr/modules/borrow/borrow_return.c scr/modules/reader/reader.c scr/modules/reservation/reservation.c scr/modules/statistic/statistic.c scr/utils/bst/bst.c scr/utils/bst/bst_stat.c scr/utils/data_io/data_io.c

if %ERRORLEVEL% == 0 (
    echo Bien dich thanh cong!
    echo De chay chuong trinh, su dung: library.exe
) else (
    echo Bien dich that bai! Kiem tra loi o tren.
)
