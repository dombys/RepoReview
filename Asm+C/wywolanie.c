#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//zadeklarowanie wywołania
extern int dodaj(int a, int b);

//funkcja na sprawdzenie czy string zawiera tylko znaki uzywane w hex
int check_Hex(const char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    if (!isxdigit(str[i])) {
      return 0;
    }
  }
  return 1;
}
//funckja dodajaca i wywolujaca
void wywolanie(int pom1, int pom2, int pom3){
dodaj(pom1, pom2);
}

//inicjalizacja programu, liczba argumentów, argumenty terminala w tablicy
int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Podano nieprawidlowa liczbe argumentow.\n");
    return 1;
  }

  //argv [1] to pierwszy parametr (adres stringa)
  //argv [2] to znak jako string
  //argv [3] to 2. string
  char *num1 = argv[1];
  char *znak = argv[2];
  char *num2 = argv[3];
  int pom1, pom2, pom3;

  //Obliczenie dlugosci stringów
  int strlen1 = strlen(num1);
  int strlen2 = strlen(num2);

  if (!check_Hex(num1)) {
    printf("Podano nieprawidlowa liczbe nr 1\n");
    return 1;
  }
  if (!check_Hex(num2)) {
    printf("Podano nieprawidlowa liczbe nr 2\n");
    return 1;
  }
  if (*znak != '+') {
    printf("Przepraszam nie wykonuje takiej operacji. Moge tylko dodawac 2 liczby.\n");
    return 1;
  }

  //przygotowanie tabel dla liczb pod konwersje oraz tablic do przeslania do pliku z funkcja dodaj
  int *wynik;
  int *przepisana;
  int *Num1;
  int *Num2;
  int *Final;

  // Alokacja pamięci dla tablic z uwzględnieniem większego stringa
  size_t maxlen = (strlen1 >= strlen2) ? strlen1 + 1 : strlen2 + 1;
  wynik = (int *)malloc(maxlen * sizeof(int));
  przepisana = (int *)malloc(maxlen * sizeof(int));
  Num1 = (int *)malloc(maxlen * sizeof(int));
  Num2 = (int *)malloc(maxlen * sizeof(int));
  Final = (int *)malloc(maxlen * sizeof(int));

  // Sprawdzenie poprawności alokacji pamięci
  if (wynik == NULL || przepisana == NULL || Num1 == NULL || Num2 == NULL || Final == NULL) {
    printf("Blad alokacji pamieci.\n");
    free(wynik);
    free(przepisana);
    free(Num1);
    free(Num2);
    free(Final);
    return 1;
  }

  // Wypełnienie tablic zerami w hex
  for (int i = 0; i < maxlen; i++) {
    wynik[i] = 0x00;
    przepisana[i] = 0x00;
    Num1[i] = 0x00;
    Num2[i] = 0x00;
    Final[i] = 0x00;
  }

  //testowe printy na wypisanie liczb podawanych w terminalu oraz na dlugosc stringa
  printf("%d\n", strlen1);
  printf("%d\n", strlen2);
  printf("Num1 to %s\n", num1);
  printf("Num2 to %s\n", num2);

  // konwersja pierwszej liczby
  for (int i = 0; i < strlen1; i++) {
    char c = num1[i];
    if (c <= '9') {
      Num1[i + 1] = c - '0';
    } else if (c <= 'F') {
      Num1[i + 1] = c - 'A' + 10;
    } else if (c <= 'f') {
      Num1[i + 1] = c - 'a' + 10;
    }
  }

  // konwersja drugiej liczby
  for (int i = 0; i < strlen2; i++) {
    char c = num2[i];
    if (c <= '9') {
      Num2[i + 1] = c - '0';
    } else if (c <= 'F') {
      Num2[i + 1] = c - 'A' + 10;
    } else if (c <= 'f') {
      Num2[i + 1] = c - 'a' + 10;
    }
  }

  //testowe wypisanie tablic przed i po konwersji hex
  printf("Num1: ");
  for (int i = 0; i < strlen1 + 1; i++) {
    printf("%x", Num1[i]);
  }
  printf("\n");

  printf("Num2: ");
  for (int i = 0; i < strlen2 + 1; i++) {
    printf("%x", Num2[i]);
  }
  printf("\n");

  //przepisanie liczb do tablic wynik i przepisana z uwzględnieniem długości
  // Wypełnienie tablic wynik i przepisana, wyrównując krótszą liczbę zerami na początku
  if (strlen1 >= strlen2) {
    for (int i = 0; i < strlen1 + 1; i++) {
      wynik[i] = Num1[i];
    }
    for (int i = 0; i < strlen2 + 1; i++) {
      int prop = strlen1 - strlen2;
      przepisana[i + prop] = Num2[i];
    }
  } else {
    for (int i = 0; i < strlen1 + 1; i++) {
      int prop = strlen2 - strlen1;
      wynik[i + prop] = Num1[i];
    }
    for (int i = 0; i < strlen2 + 1; i++) {
      przepisana[i] = Num2[i];
    }
  }

  //sprawdzenie czy przepisano dobrze
  printf("Przepisane tablice przed przekazaniem\n");
  printf("Wynik: ");
  for (int i = 0; i < maxlen; i++) {
    printf("%x", wynik[i]);
  }
  printf("\n");

  printf("Przepisana: ");
  for (int i = 0; i < maxlen; i++) {
    printf("%x", przepisana[i]);
  }
  printf("\n");

  // Wywołanie funkcji dodaj, przekazując wynik, przepisana i długość większego stringa


  if (strlen1 >= strlen2){
    for (int i = strlen1; i > 0; i--){
    pom1 = wynik[i];
    pom2 = przepisana[i];
    pom3 = dodaj(pom1, pom2);
    Final[i] = pom3;
    }
  }
  if (strlen1 < strlen2){
    for (int i = strlen2; i > 0; i--){
    pom1 = wynik[i];
    pom2 = przepisana[i];
    pom3 = dodaj(pom1, pom2);
    Final[i] = pom3;
    }
  }
  //obsługa przeniesienia
  if (strlen1 >= strlen2){
    for (int i = strlen1; i > 0; i--){
    if (Final[i] >= 0x10){
      Final[i] = Final[i] - 0x10;
      Final[i-1] = Final[i-1] + 0x01;
    }
    }
  }
  if (strlen1 < strlen2){
    for (int i = strlen2; i > 0; i--){
    if (Final[i] >= 0x10){
      Final[i] = Final[i] - 0x10;
      Final[i-1] = Final[i-1] + 0x01;
    }
    }
  }
  
 //wypisanie wyniku (kod asm modyfikuje tablicę wynik)
  printf("Wynik działania to:\n");
  for (int i = 0; i < maxlen; i++) {
    printf("%x", Final[i]);
  }
  printf("\n");
  //zwolnienie alokowanych dynamicznie tablic z pamieci
  free(wynik);
  free(przepisana);
  free(Num1);
  free(Num2);
  free(Final);
  return 0;
}
