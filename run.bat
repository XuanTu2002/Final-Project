@echo off

rem Dat code page UTF-8 cho console de hien thi tieng Viet
chcp 65001 > nul

echo === He thong Quan ly Thu vien (UTF-8) ===

rem Kiem tra xem da bien dich chua
if not exist library.exe (
    echo Dang bien dich chuong trinh...
    gcc scr\main.c scr\modules\book\book.c scr\modules\reader\reader.c scr\modules\borrow\borrow_return.c scr\modules\statistic\statistic.c scr\modules\reservation\reservation.c scr\utils\data_io\data_io.c scr\utils\bst\bst.c scr\utils\bst\bst_stat.c -o library.exe
)

rem Chay chuong trinh
library.exe
