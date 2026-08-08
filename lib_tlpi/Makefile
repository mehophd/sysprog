CC = gcc
CFLAGS = -Wall -g -I.
OBJS = error_function.o get_num.o

# Имя нашей общей статической библиотеки
LIB_NAME = libtlpi.a

all: $(LIB_NAME)

# Утилита 'ar' упаковывает .o файлы в один архив .a
$(LIB_NAME): $(OBJS)
	ar rcs $(LIB_NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(LIB_NAME)
