extern exp
global f1
global f2
global f3
global df1
global df2
global df3
global ddf1
global ddf2
global ddf3
section .data
  zero dq 0.0
  three dq 3.0
  two dq 2.0
  one dq 1.0
  minone dq -1.0
section .text
f1:
  push ebp
  mov ebp, esp
  and esp, - 16
  fld qword [zero]
  fsub qword [ebp + 8]
  fstp qword [ebp + 8]
  sub esp, 8
  push dword [ebp + 12]
  push dword [ebp + 8]
  call exp
  add esp, 16
  fadd qword [three]
  mov esp, ebp
  pop ebp
  ret
f2:
  push ebp
  mov ebp, esp
  fld qword [two]
  fmul qword [ebp + 8]
  fsub qword [two]
  mov esp, ebp
  pop ebp
  ret
f3:
  push ebp
  mov ebp, esp
  fld qword [one]
  fdiv qword [ebp + 8]
  mov esp, ebp
  pop ebp
  ret
df1:
  push ebp
  mov ebp, esp
  and esp, - 16
  fld qword [zero]
  fsub qword [ebp + 8]
  fstp qword [ebp + 8]
  sub esp, 8
  push dword [ebp + 12]
  push dword [ebp + 8]
  call exp
  fstp qword [ebp + 8]
  fld qword [zero]
  fsub qword [ebp + 8]
  add esp, 16
  mov esp, ebp
  pop ebp
  ret
df2:
  push ebp
  mov ebp, esp
  fld qword [two]
  mov esp, ebp
  pop ebp
  ret
df3:
  push ebp
  mov ebp, esp
  fld qword [minone]
  fdiv qword [ebp + 8]
  fdiv qword [ebp + 8]
  mov esp, ebp
  pop ebp
  ret
ddf1:
  push ebp
  mov ebp, esp
  and esp, - 16
  fld qword [zero]
  fsub qword [ebp + 8]
  fstp qword [ebp + 8]
  sub esp, 8
  push dword [ebp + 12]
  push dword [ebp + 8]
  call exp
  add esp, 16
  mov esp, ebp
  pop ebp
  ret
ddf2:
  push ebp
  mov ebp, esp
  fld qword [zero]
  mov esp, ebp
  pop ebp
  ret
ddf3:
  push ebp
  mov ebp, esp
  fld qword [two]
  fdiv qword [ebp + 8]
  fdiv qword [ebp + 8]
  fdiv qword [ebp + 8]
  mov esp, ebp
  pop ebp
  ret
  



