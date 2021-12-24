.text
__start:
.globl __start

lw a3, size   #a3 = числу разрядов   

li a2, 0       #a2 = 0 - изменяемое число
li a4, 1       #a4 = 1 - число шагов
li a5, 0       #a5 = 0 - счетчик

bgeu a3, a4, end_of_the_check
    jal zero, finish    #переход к завершению, если число разрядов меньше 1
end_of_the_check: 

sll a4, a4, a3    #a4 умножаем на 2 на каждый разряд

loop:
    bgeu a5, a4, finish    #счетчик итераций
    srli a6, a2, 1    #вводим вспомогательную переменную для получения числа в коде Грэя
    xor a6, a2, a6    #число в коде Грея
    print_code:
        srli a7, a4, 1    #создаем маску
        addi s4, a3, -1    #корректор для вывода
        digit:
            beq a7, zero, new_line    #счетчик выводимых разрядов
            and s2, a6, a7    #логическое умножение маски на число в коде Грея
            srl s2, s2, s4    #сдвиг для корректного вывода
            li a0, 1
            addi a1, s2, 0    #вывод разряда
            ecall
            srli a7, a7, 1    #сдвиг маски
            addi s4, s4, -1    #изменение величины корректора
            jal zero, digit    #безусловный возврат для вывода следующего разряда
    new_line:
        li a0, 4
        la a1, newline    #сдвиг на новую строку
        ecall
    addi a5, a5, 1    #увеличиваем счетчик
    addi a2, a2, 1    #увеличиваем изменяемое число
    jal zero, loop    #безусловный возврат в начало цикла

finish:
    li a0, 10
    ecall
    
.data
size:
    .word 7    #число разрядов
newline:
    .string "\n"    #константа новой строки