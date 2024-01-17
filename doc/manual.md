---
title: "Ćwiczenie 5: Obsługa przycisków i&nbsp;odkłócanie drgań styków (_debouncing_)"
subtitle: "Instrukcja laboratorium"
footer-left: "Instrukcja laboratorium"
author: [Mariusz Chilmon <<mariusz.chilmon@ctm.gdynia.pl>>]
lang: "pl"
titlepage: yes
titlepage-logo: "logo.png"
logo-width: "70mm"
colorlinks: yes
header-includes: |
  \usepackage{awesomebox}
  \usepackage{algorithm}
  \usepackage{algpseudocode}
...

> When you finally understand what you are doing, things will go right.
>
> — _Bill Fairbank_

# Cel ćwiczenia

Celem ćwiczenia jest zapoznanie się z:

* obsługą prostej klawiatury,
* programowym tłumieniem drgań styków.

# Uruchomienie programu wyjściowego

1. Podłącz płytkę _WPSH209_ do _Arduino Uno_.
1. Licznik na wyświetlaczu ma wartość `0000`.
1. Wciśnięcie przycisku _S1_ zwiększa bardzo szybko licznik.
1. Wciśnięcie przycisku _S2_ zmniejsza bardzo szybko licznik.
1. Wciśnięcie przycisku _S3_ zeruje licznik.

Procesor sprawdza w pętli głównej stan przycisku i reaguje zawsze, gdy stwierdza, że przycisk jest wciśnięty, stąd licznik jest inkrementowany z bardzo dużą prędkością przez cały czas wciśnięcia:

```cpp
if (bit_is_clear(PIN_SWITCH, BIT_SWITCH_S1)) {
    counter.increment();
}
```

\awesomebox[teal]{2pt}{\faCode}{teal}{Inkrementacja licznika jest zawuażalna tylko dlatego, że metoda \lstinline[language=c++]{counter.increment()} wykonuje operację rozbicia liczby na cyfry dziesiętne, co wymaga dzielenia, spowalniającego zawuażalnie działanie programu. Gdyby wyrugować rozbijanie liczby na cyfry, licznik osiągałby wartość \texttt{9999} w czasie rzędu milisekund.}

\awesomebox[purple]{2pt}{\faMicrochip}{purple}{Wciśnięcie przycisku zwiera pin mikrokontrolera do ujemnej szyny zasilania, więc stanem aktywnym jest \texttt{0}.}

# Zadanie podstawowe

Celem zadania podstawowego jest reagowanie tylko na wciśnięcie przycisku, nie na jego przytrzymanie.

## Wymagania funkcjonalne

1. Wciśnięcie przycisku _S1_ zwiększa liczniki o `1`.
1. Wciśnięcie przycisku _S2_ zmniejsza liczniki o `1`.
1. Wciśnięcie przycisku _S3_ zeruje licznik.
1. Dopuszczalna jest zmiana licznika o kilka jednostek w momencie wciskania i puszczania przycisków _S1_ i _S2_ ze względu na drgania styków.

W przyciskach mechanicznych występuje zjawisko drgania styków. W chwili wciskania przycisku połączenie nie następuje natychmiast, ale elementy stykowe mogą przez ułamek sekundy łączyć się i rozłączać. Analogicznie w momencie puszczania przycisku rozwarcie nie następuje od razu trwale, ale przez chwilę elementy stykowe łączą się i rozłączają.

## Modyfikacja programu

Zmodyfikuj obsługę przycisków _S1_ i _S2_ w pętli głównej (`mainLoop` w pliku `main.cpp`).

\begin{algorithm}
\caption{Reakcja tylko na wciśnięcie przycisku}
\begin{algorithmic}[1]
\If {$stanPrzycisku = 0$}
    \If {$poprzedniStanPrzycisku = 1$}
    \Comment{sprawdzamy zapisany stan przycisku}
        \State zwiększ lub zmniejsz licznik
        \State $poprzedniStanPrzycisku\gets 0$
        \Comment{zapisujemy stan przycisku}
    \EndIf
\Else
    \State $poprzedniStanPrzycisku\gets 1$
    \Comment{zapisujemy stan przycisku}
\EndIf
\end{algorithmic}
\end{algorithm}

# Zadanie rozszerzone

Celem zadania rozszerzonego jest programowa redukcja drgań styków.

## Wymagania funkcjonalne

1. Wciśnięcie przycisku _S1_ zwiększa liczniki o `1`.
1. Wciśnięcie przycisku _S2_ zmniejsza liczniki o `1`.
1. Wciśnięcie przycisku _S3_ zeruje licznik.
1. Urządzenie nie reaguje na kolejne wciśnięcia _S1_ i _S2_ przed upływem 1 sekundy.
1. Urządzenie nie reaguje na przytrzymanie przycisków.

## Modyfikacja programu

\begin{algorithm}
\caption{Reakcja tylko na wciśnięcie przycisku z eliminacją drgań}
\begin{algorithmic}[1]
\If {$stanPrzycisku = 0$}
    \If {$integrator = 0$}
        \State zwiększ lub zmniejsz licznik
    \EndIf
    \State $integrator\gets delay$
\Else
    \If {$integrator > 0$}
        \State $integrator\gets integrator - 1$
    \EndIf
\EndIf
\end{algorithmic}
\end{algorithm}
