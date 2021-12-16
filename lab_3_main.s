.text
main:
.globl main

addi sp, sp, -16    #add sp -= 16
sw ra, 12(sp)    #сохранение ссылки на возврат в прошлую подпрограмму в стек

lw s5, size
call graycode

lw ra, 12(sp)    #возврат ссылки на прошлую вызывающую подрограмму
addi sp, sp, 16    #(add) sp += 16  (возвращение sp в норму)
ret

.data
size:
    .word 7    #число разрядов
newline:
    .string "\n"    #константа новой строки