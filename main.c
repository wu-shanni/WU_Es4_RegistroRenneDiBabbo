#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    int velocita;
    int resistenza;
} Renna;

int main() {
    int fd[2];
    pipe(fd);

    pid_t pid = fork();

    if (pid == 0) {         //figlio
        close(fd[0]);           //scrive e basta

        srand(time(NULL));
        int n = rand() % 8 + 5; // 5–12 renne

        for (int i = 0; i < n; i++) {       //crea renne
            Renna r;
            sprintf(r.nome, "Renna_%d", i + 1);
            r.velocita = rand() % 51 + 50;   // 50–100
            r.resistenza = rand() % 10 + 1;  // 1–10

            write(fd[1], &r, sizeof(Renna));        //scrive i dati della struct nella pipe
        }

        // renna sentinella
        Renna sentinella = { "boh", -1, 0 };
        write(fd[1], &sentinella, sizeof(Renna));       //inviata al padre

        close(fd[1]);           //finito di scrivere
        exit(0);

    } else {            //padre
        close(fd[1]);           //legge e basta

        Renna *arr = NULL;
        int count = 0;

        while (1) {
            Renna r;
            read(fd[0], &r, sizeof(Renna));

            if (r.velocita == -1)
                break;

            arr = realloc(arr, (count + 1) * sizeof(Renna));
            arr[count] = r;
            count++;
        }

        close(fd[0]);



        printf("Renne ricevute:\n");
        for (int i = 0; i < count; i++) {
            printf("%s - vel: %d, res: %d\n",
                   arr[i].nome, arr[i].velocita, arr[i].resistenza);
        }

        // trova la più veloce
        int max = 0;
        for (int i = 1; i < count; i++)
            if (arr[i].velocita > arr[max].velocita)
                max = i;

        printf("\n%s guiderà la slitta con %d km/h!\n",
               arr[max].nome, arr[max].velocita);

        free(arr);
    }
    return 0;
}
