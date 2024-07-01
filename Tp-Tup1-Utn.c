#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHOFERES 100
#define MAX_NOMBRE 50
#define MAX_CUIL 11

typedef struct
{
    char cuil[MAX_CUIL];
    char apellido[MAX_NOMBRE];
    char nombre[MAX_NOMBRE];
    int km[5];
} Chofer;

int validar_cuil(char *cuil);
void cargar_choferes(Chofer choferes[MAX_CHOFERES], int n);
void mostrar_lista_choferes_ordenada_nombre(Chofer choferes[MAX_CHOFERES], int n);
void mostrar_lista_choferes_ordenada_kilometros(Chofer choferes[MAX_CHOFERES], int n);
void mostrar_lista_choferes_salario(Chofer choferes[MAX_CHOFERES], int n);
void buscar_chofer(Chofer choferes[MAX_CHOFERES], int n);
void mostrar_promedio_kilometros(Chofer choferes[MAX_CHOFERES], int n);
void mostrar_estadisticas(Chofer choferes[MAX_CHOFERES], int n);
int total_km_semanal(int km_dias[5]);
float promedio_km_semanal(int km_dias[5]);

int main()
{
    Chofer choferes[MAX_CHOFERES];
    int n;

    printf("Ingrese la cantidad de choferes: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_CHOFERES)
    {
        printf("Cantidad de choferes invalida.\n");
        return 1;
    }

    cargar_choferes(choferes, n);

    int opcion;
    do
    {
        printf("------------------------------------     Menu     ----------------------------------\n");
        printf(". 1 . Mostrar lista de choferes ordenada por Apellido y Nombre\n");
        printf("------------------------------------------------------------------------------------\n");
        printf(". 2 . Mostrar lista de choferes ordenada por cantidad de KM conducidos en la semana \n");
        printf("------------------------------------------------------------------------------------\n");
        printf(". 3 . Mostrar lista de choferes con su salario semanal\n");
        printf("------------------------------------------------------------------------------------\n");
        printf(". 4 . Buscar por Chofer\n");
        printf("------------------------------------------------------------------------------------\n");
        printf(". 5 . Mostrar lista de choferes con promedio de KM conducidos en la semana\n");
        printf("------------------------------------------------------------------------------------\n");
        printf(". 6 . Mostrar estadistica de choferes\n");
        printf("------------------------------------------------------------------------------------\n");
        printf("⌦⌦⌦⌦⌦⌦⌦⌦⌦⌦⌦⌦⌦⌦⌦⌦⌦⌦⌦  Salir  ⌫⌫⌫⌫⌫⌫⌫⌫⌫⌫⌫⌫⌫⌫⌫⌫⌫\n");
        printf("--------------------------   ⬇⬇ ⭮ Ingrese una opcion ⭮ ⬇⬇   ---------------------------\n");
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            mostrar_lista_choferes_ordenada_nombre(choferes, n);
            break;
        case 2:
            mostrar_lista_choferes_ordenada_kilometros(choferes, n);
            break;
        case 3:
            mostrar_lista_choferes_salario(choferes, n);
            break;
        case 4:
            buscar_chofer(choferes, n);
            break;
        case 5:
            mostrar_promedio_kilometros(choferes, n);
            break;
        case 6:
            mostrar_estadisticas(choferes, n);
            break;
        case 7:
            printf("¡¡¡ Gracias Por Usar Nuestro Sistema De Choferes UTN !!!.\n");
            break;
        default:
            printf("Opcion invalida. Intente nuevamente.\n");
        }
    } while (opcion != 7);

    return 0;
}

int validar_cuil(char *cuil)
{
    int len = strlen(cuil);
    if (len != 11)
        return 0;
    if (strncmp(cuil, "20", 2) != 0 && strncmp(cuil, "23", 2) != 0 && strncmp(cuil, "24", 2) != 0 && strncmp(cuil, "25", 2) != 0 && strncmp(cuil, "26", 2) != 0 && strncmp(cuil, "27", 2) != 0)
        return 0;
    for (int i = 0; i < len; i++)
    {
        if (!isdigit(cuil[i]))
            return 0;
    }
    return 1;
}

void cargar_choferes(Chofer choferes[MAX_CHOFERES], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Ingrese el CUIL del chofer %d: ", i + 1);
        scanf("%s", choferes[i].cuil);
        while (!validar_cuil(choferes[i].cuil))
        {
            printf("CUIL invalido. Ingrese nuevamente el CUIL del chofer %d: ", i + 1);
            scanf("%s", choferes[i].cuil);
        }
        printf("Ingrese el apellido del chofer %d: ", i + 1);
        scanf("%s", choferes[i].apellido);
        printf("Ingrese el nombre del chofer %d: ", i + 1);
        scanf("%s", choferes[i].nombre);
        for (int j = 0; j < 5; j++)
        {
            const char *dias[] = {"lunes", "martes", "miercoles", "jueves", "viernes"};
            printf("Ingrese los kilometros conducidos el %s del chofer %d: ", dias[j], i + 1);
            scanf("%d", &choferes[i].km[j]);
        }
    }
}

void mostrar_lista_choferes_ordenada_nombre(Chofer choferes[MAX_CHOFERES], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (strcmp(choferes[i].apellido, choferes[j].apellido) > 0 ||
                (strcmp(choferes[i].apellido, choferes[j].apellido) == 0 && strcmp(choferes[i].nombre, choferes[j].nombre) > 0))
            {
                Chofer temp = choferes[i];
                choferes[i] = choferes[j];
                choferes[j] = temp;
            }
        }
    }
    printf("CUIL - Apellido - Nombre\n"); // cuil y apellido juntos
    for (int i = 0; i < n; i++)
    {
        printf("%s - %s - %s\n", choferes[i].cuil, choferes[i].apellido, choferes[i].nombre);
    }
}

void mostrar_lista_choferes_ordenada_kilometros(Chofer choferes[MAX_CHOFERES], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (total_km_semanal(choferes[i].km) < total_km_semanal(choferes[j].km))
            {
                Chofer temp = choferes[i];
                choferes[i] = choferes[j];
                choferes[j] = temp;
            }
        }
    }
    printf("Apellido y Nombre - Total de KM conducidos en la semana\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s %s - %d\n", choferes[i].apellido, choferes[i].nombre, total_km_semanal(choferes[i].km));
    }
}

void mostrar_lista_choferes_salario(Chofer choferes[MAX_CHOFERES], int n)
{
    float precio_por_km;
    printf("Ingrese el precio por KM conducido: ");
    scanf("%f", &precio_por_km);

    float total_a_pagar = 0;
    printf("Apellido y Nombre - Total km semanal - Salario semanal\n");
    for (int i = 0; i < n; i++)
    {
        int km_semanal = total_km_semanal(choferes[i].km);
        float salario = km_semanal * precio_por_km;
        printf("%s %s - %d - %.2f\n", choferes[i].apellido, choferes[i].nombre, km_semanal, salario);
        total_a_pagar += salario;
    }
    printf("Importe total a abonar: %.0f\n", total_a_pagar);
}

void buscar_chofer(Chofer choferes[MAX_CHOFERES], int n)
{
    char cuil[MAX_CUIL];
    printf("Ingrese el CUIL del chofer a buscar: ");
    scanf("%s", cuil);
    while (!validar_cuil(cuil))
    {
        printf("CUIL invalido. Ingrese nuevamente el CUIL del chofer a buscar: ");
        scanf("%s", cuil);
    }

    for (int i = 0; i < n; i++)
    {
        if (strcmp(choferes[i].cuil, cuil) == 0)
        {
            printf("Chofer encontrado:\n");
            printf("CUIL: %s\n", choferes[i].cuil);
            printf("Apellido: %s\n", choferes[i].apellido);
            printf("Nombre: %s\n", choferes[i].nombre);
            printf("KM  conducidos por dia: Lunes %d, Martes %d, Miercoles %d, Jueves %d, Viernes %d\n",
                   choferes[i].km[0], choferes[i].km[1], choferes[i].km[2], choferes[i].km[3], choferes[i].km[4]);
            printf("Total de KM conducidos en la semana: %d\n", total_km_semanal(choferes[i].km));
            return;
        }
    }
    printf("No existe chofer con ese CUIL.\n");
}

void mostrar_promedio_kilometros(Chofer choferes[MAX_CHOFERES], int n)
{
    printf("CUIL - Apellido y Nombre - Promedio de KM conducidos en la semana\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s - %s %s - %.2f\n", choferes[i].cuil, choferes[i].apellido, choferes[i].nombre, promedio_km_semanal(choferes[i].km));
    }
}

void mostrar_estadisticas(Chofer choferes[MAX_CHOFERES], int n)
{
    int max_km = 0, min_km = total_km_semanal(choferes[0].km);
    float max_prom_km = 0, min_prom_km = promedio_km_semanal(choferes[0].km);
    int total_km = 0;
    Chofer *max_km_chofer = &choferes[0], *min_km_chofer = &choferes[0], *max_prom_km_chofer = &choferes[0], *min_prom_km_chofer = &choferes[0];
    for (int i = 0; i < n; i++)
    {
        int total = total_km_semanal(choferes[i].km);
        float promedio = promedio_km_semanal(choferes[i].km);
        total_km += total;

        if (total > max_km)
        {
            max_km = total;
            max_km_chofer = &choferes[i];
        }
        if (total < min_km)
        {
            min_km = total;
            min_km_chofer = &choferes[i];
        }
        if (promedio > max_prom_km)
        {
            max_prom_km = promedio;
            max_prom_km_chofer = &choferes[i];
        }
        if (promedio < min_prom_km)
        {
            min_prom_km = promedio;
            min_prom_km_chofer = &choferes[i];
        }
    }

    printf("El chofer con mayor cantidad de KM conducidos en la semana es %s %s con %d km\n", max_km_chofer->apellido, max_km_chofer->nombre, max_km);
    printf("El chofer con menor cantidad de KM conducidos en la semana es %s %s con %d km\n", min_km_chofer->apellido, min_km_chofer->nombre, min_km);
    printf("El chofer con mayor promedio de KM conducidos en la semana es %s %s con %.0f km\n", max_prom_km_chofer->apellido, max_prom_km_chofer->nombre, max_prom_km);
    printf("El chofer con menor promedio de KM conducidos en la semana es %s %s con %.0f km\n", min_prom_km_chofer->apellido, min_prom_km_chofer->nombre, min_prom_km);
    printf("El promedio total de kilómetros KM por todos los choferes es %.0f km\n", (float)total_km / n);
}

int total_km_semanal(int km_dias[5])
{
    return km_dias[0] + km_dias[1] + km_dias[2] + km_dias[3] + km_dias[4];
}

float promedio_km_semanal(int km_dias[5])
{
    return total_km_semanal(km_dias) / 5.0;
}