# Опция для сборки под разные дистрибутивы и системы. Необходимо
# указывать вручную, кроме сборки под mac (mac определяется автоматически).
# Задать в консоли: make ... DISTRO=2
# Значения: 1 (Arch & Alpine, по умолчанию)
# 		    2 (Ubuntu & Debian)
#			3 (принудительно собрать под Darvin)
DISTRO?=1
# Ручной выбор библиотек, с которыми программа будет собираться
# Задать в консоли: make ... SYS_LIBS="-lm"
# или написать прямо здесь, в переменной
SYS_LIBS=

# Опция для выбора флагов сборки: 
# При каждой пересборке делать clean!
# Значения: 1 (стандартный режим, без отладочной информациии) 111 строка
# 		    2 (сборка с "санитайзерами", без отладочной информациии) 89 строка
#			3 (сборка с отладочной информацией для valgrind, gdb и тп.) 96 строка
#			4 (сборка "ничего святого") 102 строка
MODE?=1

# Название хеддера библиотеки
HEADER_NAME = quadratic_equation.h
# Папки с исходниками библиотеки (можно указать как отдельные 
# модули, так и общую для всех модулей папку)
SOURCE_DIR = src
# Папка с тестами 
TESTS_DIR = test
# Название файлов библиотеки
STATIC_LIB = quadratic_equation.a
STATIC_LIB_GCOV = quadratic_equation_gcov.a

# Файл для ручной отладки
DEBUG_SOURCE = test/debug.c
# Его исполняемый файл
DEBUG_EXE = debug
# Исполняемые файлы тестов
TEST_EXE = TEST
GCOV_EXE = GCOV_EXE

# Файл куда пишутся логи тестов
TEST_TXT = test_log.txt
# Файл куда пишутся логи валгринда
VALGRIND_TXT = vgoutput.txt

# Папка для объектных файлов (в корне лежат файлы библиотеки)
OBJ_DIR = object_files_tmp
# Папка для отчета
# REPORT_DIR = report_tmp
REPORT_DIR = $(OBJ_DIR)/report_tmp

# Следите за тем, чтобы названия временных папок OBJ_DIR и REPORT_DIR 
# не совпадали с названиями папок с исходными файлами!

#       Конец изменяемых параметров

OS := $(shell uname -s)

CUSTOM_SYS_LIBS=0
ifeq ($(DISTRO), 3) # принудительно собрать под Darvin
	CMD_OPEN ?= open
	ifneq ($(strip $(SYS_LIBS)),) 
		CUSTOM_SYS_LIBS=1
	endif
else ifeq ($(OS), Linux)
	CMD_OPEN ?= xdg-open # Нужен пакет xdg-utils
	ifneq ($(strip $(SYS_LIBS)),) 
		CUSTOM_SYS_LIBS=1
	else
		ifeq ($(DISTRO), 1) # Arch & Alpine
			SYS_LIBS = -lm 
		else ifeq ($(DISTRO), 2) # Ubuntu & Debian
			SYS_LIBS = -lm -pthread -lsubunit -lrt
		else
			$(info WARNING - Linux distribution variable has been assigned an incorrect value. \
			Instead, the default value is assigned (successful completion of the build process is not guaranteed).)
			SYS_LIBS = -lm
		endif
	endif
else ifeq ($(OS), Darwin) 
	CMD_OPEN ?= open
	ifneq ($(strip $(SYS_LIBS)),) 
		CUSTOM_SYS_LIBS=1
	endif
else
	$(error OS is neither Linux nor Darwin. OS value: $(OS))
endif

# Флаги (при каждой пересборке делать clean!)
ifeq ($(MODE), 2)
	LFLAGS= -fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover \
	-fstack-protector -fanalyzer
	CFLAGS_TESTS=-fsanitize=address -Wall -Werror -Wextra -fsanitize=leak -fsanitize=undefined -fsanitize=unreachable \
	-fno-sanitize-recover -fstack-protector #-fanalyzer
	CFLAGS += $(CFLAGS_TESTS) -fanalyzer
else 
	ifeq ($(MODE), 3)
# Сборка с отладочной информацией для valgrind
		LFLAGS=-g
		CFLAGS=-Wall -Werror -Wextra -g
		CFLAGS_TESTS = $(CFLAGS)
	else 
		ifeq ($(MODE), 4)
# Сборка со всеми флагами 
			LFLAGS= -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector -fanalyzer
			CFLAGS=-Wall -Werror -Wextra -O2 -pedantic -std=c11 -Wshadow -Wlogical-op -Wshift-overflow=2 \
			-Wduplicated-cond -Wcast-align -Wfloat-equal -Wconversion -Wcast-qual -D_GLIBCXX_DEBUG \
			-D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined \
			-fno-sanitize-recover -fstack-protector -fanalyzer
			CFLAGS_TESTS = $(CFLAGS) -fanalyzer
		else
# Стандартный режим
			LFLAGS= 
			CFLAGS=-Wall -Werror -Wextra -std=c11 -pedantic
			CFLAGS_TESTS = $(CFLAGS)
		endif
	endif
endif

CC = gcc
LD = gcc
GCOV_FLAGS =-fprofile-arcs -ftest-coverage

# Папка для объектных файлов тестов
GCOV_OBJ_DIR = $(OBJ_DIR)/gcov_tmp
TESTS_OBJ_DIR = $(OBJ_DIR)/tests_tmp

# Библиотеки (этап линковки)
ifeq ($(CUSTOM_SYS_LIBS), 0)
	LIBS := -lcheck $(SYS_LIBS) 
	LIBS_GCOV := $(LIBS) -lgcov
else
	LIBS ?= $(SYS_LIBS)
	LIBS_GCOV ?= $(LIBS)
endif

# Наполнение переменных списками директорий, исходных и исполняемых файлов
ALL_SOURCE_DIRS = $(shell find $(SOURCE_DIR) -type d)
LIB_SOURCE_FILES = $(notdir $(shell find $(ALL_SOURCE_DIRS) -maxdepth 1 -name "*.c"))
LIB_HEADERS = $(shell find $(ALL_SOURCE_DIRS) -maxdepth 1 -name "*.h")
LIB_MAIN_HEADER = $(shell find . -name "$(HEADER_NAME)")
LIB_OBJ_FILES = $(LIB_SOURCE_FILES:%.c=%.o)

ALL_TESTS_DIRS = $(shell find $(TESTS_DIR) -type d)
# TEST_SOURCE_FILES = $(notdir $(shell find $(ALL_TESTS_DIRS) -maxdepth 1 -name "*.c"))
TEST_SOURCE_FILES := $(notdir $(shell find $(ALL_TESTS_DIRS) -maxdepth 1 -name "*.c"))
TEST_SOURCE_FILES := $(filter-out $(notdir $(DEBUG_SOURCE)), $(TEST_SOURCE_FILES))
TEST_HEADERS = $(shell find $(ALL_TESTS_DIRS) -maxdepth 1 -name "*.h")
TEST_OBJ_FILES = $(addprefix $(TESTS_OBJ_DIR)/, $(TEST_SOURCE_FILES:%.c=%.o))

GCOV_CHECKED_OBJ = $(addprefix $(GCOV_OBJ_DIR)/, $(notdir $(LIB_SOURCE_FILES:.c=.o)))

ALL_LIB_HEADERS = $(LIB_HEADERS) $(LIB_MAIN_HEADER)
ALL_HEADERS = $(ALL_LIB_HEADERS) $(TEST_HEADERS)

# Списки каталогов, в которых make выполняет поиск соответствующих типов файлов
vpath %.c $(ALL_SOURCE_DIRS) $(ALL_TESTS_DIRS)
vpath %.o $(OBJ_DIR)

# Неявные правила (Implicit Rules) 
%.o : %.c $(ALL_LIB_HEADERS)
	$(CC) -c $(CFLAGS) -o $(OBJ_DIR)/$@ $<

$(TESTS_OBJ_DIR)/%.o : %.c $(ALL_HEADERS)
	$(CC) -c $(CFLAGS_TEST) -o $@ $<

$(GCOV_OBJ_DIR)/%.o : %.c $(ALL_HEADERS)
	$(CC) -c $(CFLAGS) $(GCOV_FLAGS) -o $@ $<

.PHONY: all clean rebuild debug test gcov_report clang valgrind
#.DEFAULT_GOAL := debug

all: test gcov_report

debug: $(STATIC_LIB)
	$(LD) $(LFLAGS) $(DEBUG_SOURCE) $(STATIC_LIB) $(LIBS) -o $(DEBUG_EXE)
	./$(DEBUG_EXE)

check : test

test: $(TESTS_OBJ_DIR) $(STATIC_LIB) $(TEST_OBJ_FILES) $(ALL_HEADERS)
	$(LD) $(LFLAGS) $(TEST_OBJ_FILES) $(STATIC_LIB) $(LIBS) -o $(TEST_EXE) 
	-./$(TEST_EXE)

gcov : gcov_report

gcov_report: $(GCOV_OBJ_DIR) $(REPORT_DIR) $(STATIC_LIB_GCOV) $(TEST_OBJ_FILES) $(ALL_HEADERS) 
	$(LD) $(LFLAGS) $(TEST_OBJ_FILES) $(STATIC_LIB_GCOV) $(LIBS_GCOV) -o ./$(GCOV_EXE)
	-./$(GCOV_EXE)
	gcov -o $(GCOV_OBJ_DIR) $(LIB_SOURCE_FILES)
	lcov -b ./ -d $(GCOV_OBJ_DIR) --gcov-tool /usr/bin/gcov -c -o output.info
	genhtml -o $(REPORT_DIR) output.info
	@-rm *.c.gcov output.info
	$(CMD_OPEN) $(REPORT_DIR)/index.html

$(STATIC_LIB): $(OBJ_DIR) $(LIB_OBJ_FILES) $(ALL_LIB_HEADERS) 
	ar rc $(STATIC_LIB) $(addprefix $(OBJ_DIR)/, $(LIB_OBJ_FILES))
	ranlib $(STATIC_LIB)

$(STATIC_LIB_GCOV): $(GCOV_OBJ_DIR) $(TESTS_OBJ_DIR) $(GCOV_CHECKED_OBJ)  $(ALL_HEADERS)
	ar rc $(STATIC_LIB_GCOV) $(GCOV_CHECKED_OBJ)
	ranlib $(STATIC_LIB_GCOV)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TESTS_OBJ_DIR):
	mkdir -p $(TESTS_OBJ_DIR)

$(GCOV_OBJ_DIR):
	mkdir -p $(GCOV_OBJ_DIR)

$(REPORT_DIR):
	mkdir -p $(REPORT_DIR)

clang:
	find . -type f \( -name "*.c" -o -name "*.h" \) -exec sh -c 'echo >> "$$1"' _ {} \;
	find . -type f -name "*.c" -o -name "*.h" | xargs clang-format -i

valgrind: test
	2>&1 valgrind --log-file="$(VALGRIND_TXT)" --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./$(TEST_EXE)
	grep "ERROR SUMMARY" $(VALGRIND_TXT)

c : clean

clean:
	@-rm -rf $(OBJ_DIR) $(TESTS_OBJ_DIR) $(REPORT_DIR)
	@-rm -f $(STATIC_LIB) $(STATIC_LIB_GCOV) $(TEST_EXE) $(DEBUG_EXE) $(GCOV_EXE) $(VALGRIND_TXT) .clang-format 

r : rebuild

rebuild: clean all
