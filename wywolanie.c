#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//zadeklarowanie wywoalania
extern void dodaj (int *a, int *b, int c);

//funkcja na sprawdzenie czy string zawiera tylko znaki uzywane w hex
int check_Hex(const char *str) {
  for(int i=0; str[i] != '\0'; i++) {
    if (!isxdigit(str[i])) {
      return 0;
    }
  }
  return 1;
}
//inicjalizacja programu, liczba argumentów, argumenty terminala w tablicy
int main (int argc, char *argv[]){

  if (argc !=4) {
    printf ("Podano nieprawidlowa liczbe argumentow.\n");
    return 1;
  }
//argv [1] to pierwszy parametr (adres stringa)
//argv [2] to znak jako string
//argv [3] to 2. string
char *num1 = argv[1];
char *znak = argv[2];
char *num2 = argv[3];
//Obliczenie dlugosci stringów
int strlen1 = strlen(num1);
int strlen2 = strlen(num2);

if (!check_Hex(num1)){
    printf ("Podano nieprawidlowa liczbe nr 1\n");
    return 1;
  }

if (!check_Hex(num2)){
    printf ("Podano nieprawidlowa liczbe nr 2\n");
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

//alokacja pamieci dla tablic
if (strlen1 >= strlen2){
  size_t n = strlen1 + 1;
  wynik = (int*)malloc(n*sizeof(int));
  for (int i=0; i<strlen1+1;i++){ //zapełnienie tablicy zerami w hex
  wynik[i]=0x00;
  }
}
else {
  size_t n = strlen2 + 1;
  wynik = (int*)malloc(n*sizeof(int));
  for (int i=0; i<strlen2+1;i++){ //zapełnienie tablicy zerami w hex
  wynik[i]=0x00;
  }
}
if (wynik == NULL) {
  printf("Blad alokacji pamieci. Sprawdz deklaracje tablicy wynik\n");
  return 1;
}
if (strlen1 >= strlen2){
  size_t n = strlen1 + 1;
  przepisana = (int*)malloc(n*sizeof(int));
  for (int i=0; i<strlen1+1;i++){
  przepisana[i]=0x00;
  }
}
else {
  size_t n = strlen2 + 1;
  przepisana = (int*)malloc(n*sizeof(int));
  for (int i=0; i<strlen2+1;i++){
  przepisana[i]=0x00;
  }
}

if (przepisana == NULL) {
  printf("Blad alokacji pamieci. Sprawdz deklaracje tablicy przepisana\n");
  free(wynik);
  return 1;
}
if (strlen1 >= strlen2){
  size_t n = strlen1 + 1;
  Num1 = (int*)malloc(n*sizeof(int));
  for (int i=0; i<strlen1+1;i++){
  Num1[i]=0x00;
  }
}
else {
  size_t n = strlen2 + 1;
  Num1 = (int*)malloc(n*sizeof(int));
  for (int i=0; i<strlen2+1;i++){
  Num1[i]=0x00;
  }
}

if (przepisana == NULL) {
  printf("Blad alokacji pamieci. Sprawdz deklaracje tablicy Num1\n");
  free(wynik);
  free(przepisana);
  return 1;
}

if (strlen1 >= strlen2){
  size_t n = strlen1 + 1;
  Num2 = (int*)malloc(n*sizeof(int));
  for (int i=0; i<strlen1+1;i++){
  Num2[i]=0x00;
  }
}
else {
  size_t n = strlen2 + 1;
  Num2 = (int*)malloc(n*sizeof(int));
  for (int i=0; i<strlen2+1;i++){
  Num2[i]=0x00;
  }
}

if (przepisana == NULL) {
  printf("Blad alokacji pamieci. Sprawdz deklaracje tablicy Num2\n");
  free(wynik);
  free(przepisana);
  free(Num1);
  return 1;
}
//testowe printy na wypisanie liczb podawanych w terminalu oraz na dlugosc stringa
printf("%d\n", strlen1);
printf("%d\n", strlen2);
printf ("Num1 to %s\n", num1);
printf ("Num2 to %s\n", num2);

for (int i=0; i <strlen1; i++){
char c = num1[i];
  if (c <='9'){
    Num1[i+1] = c - '0';
  }
  else if (c <='F') {
    Num1[i+1] = c - 'A' + 10;
  }
  else if (c <='f') {
    Num1[i+1] = c - 'a' + 10;
  }
}
// konwersja drugiej liczby
for (int i=0; i <strlen2; i++){
char c = num2[i];
  if (c <='9'){
    Num2[i+1] = c - '0';
  }
  else if (c <='F') {
    Num2[i+1] = c - 'A' + 10;
  }
  else if (c <='f') {
    Num2[i+1] = c - 'a' + 10;
  }
}
//testowe wypisanie tablic przed i po konwersji hex
for (int i=0; i<strlen1; i++){
printf ("%x", num1[i]);
}
printf("\n");
for (int i=0; i<strlen2; i++){
printf ("%x", num2[i]);
}
printf("\n");
for (int i=0; i<strlen1+1; i++){
printf ("%x", Num1[i]);
}
printf("\n");
for (int i=0; i<strlen2+1; i++){
printf ("%x", Num2[i]);
}
printf("\n");

//przepisanie liczb do tablic wynik i przepisana zależnie od ich długości
if (strlen1 ==strlen2){
  for(int i=0; i < strlen1+1; i++){
  wynik[i] = Num1[i];
  przepisana[i] = Num2[i];
  }
}
if (strlen1 > strlen2){
  for(int i=0; i < strlen1+1; i++){
  wynik[i] = Num1[i];
  }
  for(int i=0; i < strlen2+1; i++){
  int prop = strlen1 - strlen2;
  przepisana[i+prop] = Num2[i];
  }
}
if (strlen1 < strlen2){
  for(int i=0; i < strlen1+1; i++){
  int prop = strlen2 - strlen1;
  wynik[i+prop] = Num1[i];
  }
  for(int i=0; i < strlen2+1; i++){
  przepisana[i] = Num2[i];
  }
}

//sprawdzenie czy przepisano dobrze
printf("Przepisane tablice przed przekazaniem\n");
if (strlen1 ==strlen2){
for (int i=0; i<strlen1+1; i++){
printf ("%x", wynik[i]);
}
printf("\n");
for (int i=0; i<strlen1+1; i++){
printf ("%x", przepisana[i]);
}
printf("\n");
}

if (strlen1 > strlen2){
for (int i=0; i<strlen1+1; i++){
printf ("%x", wynik[i]);
}
printf("\n");
for (int i=0; i<strlen1+1; i++){
printf ("%x", przepisana[i]);
}
printf("\n");
}

if (strlen1 < strlen2){
for (int i=0; i<strlen2+1; i++){
printf ("%x", wynik[i]);
}
printf("\n");
for (int i=0; i<strlen2+1; i++){
printf ("%x", przepisana[i]);
}
printf("\n");
}


/*
dodaj(Num1, Num2, strlen1);
*/

//wypisanie wyniku (kod asm modyfikuje tablicę wynik)
if (strlen1 == strlen2){
for (int i=0; i<strlen1+1; i++){
printf ("%x", wynik[i]);
}
printf("\n");

if (strlen1 > strlen2){
for (int i=0; i<strlen1+1; i++){
printf ("%x", wynik[i]);
}
printf("\n");

if (strlen1 < strlen2){
for (int i=0; i<strlen2+1; i++){
printf ("%x", wynik[i]);
}
printf("\n");
//zwolnienie alokowanych dynamicznie tablic z pamieci
free(wynik);
free(przepisana);
free(Num1);
free(Num2);
return 0;
}
