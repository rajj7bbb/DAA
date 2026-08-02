#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    FILE *fp;
    FILE *gnuplot;
    int n, moves;

    fp = fopen("toh.dat", "w");

    // Generate data for 1 to 15 disks
    for (n = 1; n <= 15; n++)
    {
        moves = (int)pow(2, n) - 1;
        fprintf(fp, "%d %d\n", n, moves);
        printf("Disks = %2d   Moves = %d\n", n, moves);
    }

    fclose(fp);

    // Open Gnuplot
    gnuplot = popen("gnuplot -persistent", "w");

    fprintf(gnuplot, "set title 'Tower of Hanoi Analysis'\n");
    fprintf(gnuplot, "set xlabel 'Number of Disks'\n");
    fprintf(gnuplot, "set ylabel 'Number of Moves'\n");
    fprintf(gnuplot, "set grid\n");
    fprintf(gnuplot, "set style data linespoints\n");
    fprintf(gnuplot, "plot 'toh.dat' using 1:2 title 'Moves (2^n - 1)' lw 2 pt 7\n");

    fflush(gnuplot);
    pclose(gnuplot);

    return 0;
}