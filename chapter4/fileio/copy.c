#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#ifndef BUF_SIZE        /* Позволяет "gcc -D" перекрыть определение */
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[]) {
    int inputFd, outputFd, openFlags;
    int forceFlag = 0;
    mode_t filePerms;
    ssize_t numRead;
    char buf[BUF_SIZE];

    if (argc < 3 || argc > 4 || strcmp(argv[1], "--help") == 0)
        usageErr("%s old-file new-file [--force]\n", argv[0]);
    /* Открытие файлов ввода и вывода */
    inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1)
        errExit("opening file %s", argv[1]);
    
    if (argc == 4 && strcmp(argv[3], "--force") == 0)
        forceFlag = 1;

    if (forceFlag) {
        openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    } else {
        openFlags = O_CREAT | O_WRONLY | O_EXCL;
    }
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH;
    /*
    Выше через побитовое ИЛИ задаются права доступа из <sys/stat.h>, справка по ним ниже
    O_WRONLY (Write Only):Открывает файл исключительно для записи данных.Чтение через read() будет запрещено.
    O_CREAT (Create):Создает файл, если его еще нет на диске.Если файл есть, этот флаг просто игнорируется.
    Важно: При использовании O_CREAT функция open() требует третий аргумент — права доступа (например, 0644).
    O_TRUNC (Truncate):Обрезает длину существующего файла до 0 байт.Всё старое содержимое полностью удаляется при открытии.
    S_IRUSR (Read User): Владелец файла может читать файл.
    S_IWUSR (Write User): Владелец файла может записывать в файл.
    S_IRGRP (Read Group): Члены группы владельца могут читать файл.
    S_IWGRP (Write Group): Члены группы владельца могут записывать в файл.
    S_IROTH (Read Others): Все остальные пользователи могут читать файл.
    S_IWOTH (Write Others): Все остальные пользователи могут записывать в файл.
    */
    outputFd = open(argv[2], openFlags, filePerms); // Собственно здесь открывается/создается файл для записи с нашими правами
    if (outputFd == -1)
        errExit("opening file %s", argv[2]);

    /* Перемещение данных до достижения конца файла ввода или возникновения ошибки */
    while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0)
        if (write(outputFd, buf, numRead) != numRead)
            fatal("couldn't write whole buffer");

    /*
    while ((numRead = read(...)) > 0): 
    Цикл выполняется до тех пор, пока read возвращает число больше нуля. 
    read читает из inputFd порцию данных размером не более BUF_SIZE и кладет её в buf. 
    Возвращает она фактическое количество прочитанных байт. 
    Когда файл закончится, read вернет 0, и цикл завершится.
    
    if (write(outputFd, buf, numRead) != numRead): 
    Внутри цикла функция write пытается записать в outputFd ровно то количество байт (numRead), 
    которое только что было успешно прочитано из первого файла. 
    Если write возвращает число, не равное numRead (например, на диске закончилось место), 
    это считается критической ошибкой, и функция fatal аварийно завершает программу.
    */
    if (numRead == -1)
        errExit("read");
    if (close(inputFd) == -1)
        errExit("close input");
    if (close(outputFd) == -1)
        errExit("close output");

    exit(EXIT_SUCCESS);
}