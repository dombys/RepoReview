#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
//definiujemy strukturę podstawowego pliku .wav PMC (bez dodatkowych chunków w FMT)
typedef struct{
char RIFF[4]; //RIFF 4 bajty
int ChunkSize; //wielkość pliku bez pierwszych 8 bajtów (bez pierwszych 2 chunków)
char Format[4]; //format
char FMT[4]; //subchunk FMT 4 bajty
int Subchunk1Size; //16 dla PCM
short AudioFormat; //1 dla PCM; 2 bajty, dlatego short
short NumChannels; //szukamy 1, bo mono; stereo to 2
int SampleRate;
int ByteRate; //SampleRate * NumChannels *BitsPerSample/8
short BlockAlign; //liczba bitów jednej próbki NumChannels*BitsPerSample/8
short BitsPerSample; //szukamy 16, zgodnie z projektem.
char DATA[4]; //słowo DATA w hex
int DataSize; //NumSamples*NumChannels*BitsPerSample/8
}HeaderOfPMCWavFile;
//w dalszej części pliku już są sample
//funkcja wrzucająca do asm
extern void obrobka(int *a, int b, float c, int d);

//inicjalizacja programu, liczba argumentów, argumenty terminala w tablicy
int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Podano nieprawidlowa liczbe argumentow.\n");
	printf("Akceptowane wywołanie: /nazwa_programu nazwa_pliku_wav opoznienie wzmocnienie\n");
    return 1;
  }
//deklarujemy wskaźniki na wartości z terminala
char *nazwa_pliku = argv[1];
char *temp1 = argv[2];
char *temp2 = argv[3];

float a, td; //współczynnik wygaszenia/wzmocniea, td - czas opóźnienia
td = atof (temp1);
a = atof (temp2);

FILE *wskaz_plik;
wskaz_plik = fopen (nazwa_pliku,"rb+"); //r+b albo rb+ bo chcemy read i write w binarce
if(wskaz_plik==NULL){
 printf("Podano nieprawidłowy plik\n");
 return 1; 
}
HeaderOfPMCWavFile header_pliku; //deklarujemy strukturę o nazwie header_pliku o typie struktury z początku
//odczytujemy dane z pliku do bufora, minimalnej wielkości, maxymalna liczba elementów, z czego
//inaczej pisząc -> do strukty header_pliku wpisujemy JEDNOKROTNIE, tyle ile header pomieści z pliku
fread(&header_pliku, sizeof(HeaderOfPMCWavFile), 1, wskaz_plik);
printf("We are in and ready to do things\n");
/*char buf[18];
fgets(buf, 18, wskaz_plik); //testowanie na pliku .txt czy pobierze chociaz 18 charkow z pliku
printf("We are in\n");
printf("%s\n",buf);*/
//testowe wypisanie interesujących elementów pliku
/*
printf("Subchunk1Size: %i\n", header_pliku.Subchunk1Size);
printf("AudioFormat: %i\n", header_pliku.AudioFormat);
printf("SampleRate: %i\n", header_pliku.SampleRate);
printf("NumChannels: %i\n", header_pliku.NumChannels);
printf("BitsPerSample: %i\n", header_pliku.BitsPerSample);
printf("DataSize: %i\n", header_pliku.DataSize);
*/
if(strncmp(header_pliku.RIFF, "RIFF", 4) !=0){
printf("Wczytaj poprawny plik typu RIFF\n");
return 1;
}
if(strncmp(header_pliku.Format, "WAVE", 4) !=0){
printf("Wczytaj poprawny plik o formacie Wave\n");
return 1;
}
if (header_pliku.AudioFormat!=1){
printf("Podany plik audio nie jest skompresowany w formacie PCM. Wczytaj poprawny plik.\n");
return 1;
}
if (header_pliku.NumChannels!=1){
printf("Podany plik nie jest typu mono. Wczytaj poprawny plik.\n");
return 1;
}
if (header_pliku.BitsPerSample!=16){
printf("Podany plik nie posiada 16 bitow/probke audio. Wczytaj poprawny plik.\n");
return 1;
}
//liczenie tx
int tx = header_pliku.SampleRate*td;
//liczenie liczbypróbek
int NumOfSamples = header_pliku.DataSize/(header_pliku.BitsPerSample/8);
int *sample_arr;
//array o wielkości sampli w każdym miejsce na 16-bit sampla - short to 2 bajty
sample_arr = (int *)malloc(NumOfSamples*sizeof(int));
if(sample_arr == NULL){
printf("Bład alokacji tablicy dla probek\n");
return 1;
}

fread(sample_arr, header_pliku.DataSize,1,wskaz_plik);

fclose(wskaz_plik);

wskaz_plik = fopen (nazwa_pliku,"rb+"); //r+b albo rb+ bo chcemy read i write w binarce
if(wskaz_plik==NULL){
 printf("Podano nieprawidłowy plik\n");
 return 1; 
}
printf("Tx: %d\n", tx); //testowe wypisanie tx
printf("Liczba probek: %i\n", NumOfSamples); //testowe wypisanie liczby próbek
obrobka(sample_arr, NumOfSamples, a, tx);

fwrite (&header_pliku, sizeof(HeaderOfPMCWavFile),1,wskaz_plik);

fwrite(sample_arr, header_pliku.DataSize,1,wskaz_plik);


free(sample_arr);
fclose(wskaz_plik);
return 0;
}
