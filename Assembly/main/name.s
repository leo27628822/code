        .data
team:   .asciz "Team 11\n"
mem1:   .asciz "Leo\n"
mem2:   .asciz "Atialon\n"
mem3:   .asciz "Dainel\n"

        .text
        .global main

main:   stmfd   sp!, {lr}
        ldr     r0, =mem1
        bl      printf
        mov     r0, #0
        ldmfd   sp!, {lr}
        mov     pc, lr
