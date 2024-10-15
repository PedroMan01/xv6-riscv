#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "syscall.h"


extern struct {
    struct spinlock lock;
} cons;


uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// Agrega esta función a kernel/sysproc.c
// kernel/sysproc.c

// Función auxiliar para obtener el ancestro
uint64
get_ancestor(int level)
{
    struct proc *p = myproc();

    // Aquí deberías implementar la lógica para obtener el ancestro
    // Devolver un valor de ejemplo, por ejemplo, el PID del proceso padre
    // Aquí solo devolvemos el PID del proceso padre para ilustrar
    return p->parent ? p->parent->pid : -1;
}
uint64
sys_console_acquire(void) {
    acquire(&cons.lock);  // Adquirimos el lock de la consola
    return 0;
}

uint64
sys_console_release(void) {
    release(&cons.lock);  // Liberamos el lock de la consola
    return 0;
}

