#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

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

//---------------------------------------------------------
uint64
sys_mprotect(void)
{
    uint64 addr;
    int len;

    // Usamos argaddr para obtener un argumento uint64
    argaddr(0, &addr); 
    argint(1, &len);

    // Imprime las direcciones recibidas y el tamaño
    printf("Dirección: %p, Tamaño: %d\n", (void*)addr, len);

    struct proc *p = myproc();
    uint start = PGROUNDDOWN(addr); // Redondea hacia abajo para la página
    uint end = PGROUNDUP(addr + len * PGSIZE); // Redondea hacia arriba

    // Imprime el rango de direcciones que se va a proteger
    printf("Rango de memoria a proteger: [%lx - %lx]\n", (long)start, (long)end);

    // Verifica que el rango sea válido
    if (start >= end || end > KERNBASE) {
        printf("Rango inválido de direcciones: [%lx - %lx]\n", (long)start, (long)end);
        return -1;
    }

    // Recorre cada página en el rango
    for (uint a = start; a < end; a += PGSIZE) {
        pte_t *pte = walk(p->pagetable, a, 0); // Cambia walkaddr por walk


        // Imprime información sobre la página de la tabla de páginas
        if (pte == 0) {
            printf("No se encontró entrada de tabla para la dirección: %lx\n", (long)a);
            return -1;
        }

        // Imprime el valor de la entrada de la tabla de páginas antes de modificarla
        printf("PTE antes de modificar (dirección %lx): %lx\n", (long)a, (long)*pte);

        if ((*pte & PTE_V) == 0) {
            printf("Página no válida para la dirección: %lx\n", (long)a);
            return -1;
        }

        // Desactiva el bit de escritura
        *pte &= ~PTE_W;
        
        // Imprime el valor de la entrada de la tabla de páginas después de modificarla
        printf("PTE después de modificar (dirección %lx): %lx\n", (long)a, (long)*pte);
    }

    // Instrucción de barrera para actualizar TLB
    sfence_vma();

    // Confirma que la protección se haya aplicado correctamente
    printf("Memoria protegida con éxito.\n");

    return 0;
}

// Restaura permisos de lectura/escritura
uint64
sys_munprotect(void)
{
    uint64 addr; // Cambiar a uint64
    int len;
    // Usamos argaddr para obtener un argumento uint64
    argaddr(0, &addr);
    argint(1, &len);

    struct proc *p = myproc();
    uint start = PGROUNDDOWN(addr);
    uint end = PGROUNDUP(addr + len * PGSIZE);

    if (start >= end || end > KERNBASE)
        return -1;

    for (uint a = start; a < end; a += PGSIZE) {
        pte_t *pte = walk(p->pagetable, a, 0);
        printf("PTE antes de modificar en munprotect (dirección %lx): %lx\n", (long)a, (long)*pte);
        if (pte == 0 || (*pte & PTE_V) == 0)
            return -1;
        *pte |= PTE_W; // Reactivar el bit de escritura
        printf("PTE después de modificar en munprotect (dirección %lx): %lx\n", (long)a, (long)*pte);

    }
    sfence_vma(); // Instrucción de barrera para actualizar TLB
    return 0;
}
//---------------------------------------------------------