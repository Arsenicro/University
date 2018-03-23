# Projektowanie i implementacja zaawansowanych aplikacji PHP

## Diamond Words


### Zadanie

Napisz program, który odczyta z parametrów przekazanych do skryptu CLI listę słów, a następnie wyświetli na standardowym wyjściu poszczególne słowa wpisane we wzór diamentu.
 
Środkowa linia diamentu zawiera pełne słowo, każda linia w górę i w dół zawiera wycentrowane słowo okrojone o pierwszą i ostatnią literę, aż do końca wzoru diamentu. Poszczególne wzory powinny być odseparowane pustym wierszem, a każda linia wygenerowane przez program powinna na początku zawierać informację o liczbie liter w danej linii.


### Przykład

Wywołanie programu:

```
php diamond-words.php ALA PROGRAM
```

Wynik:

```
1  A
3 ALA
1  A
0
1    G
3   OGR
5  ROGRA
7 PROGRAM
5  ROGRA
3   OGR
1    G
```

### Uwagi

Program będzie uruchamiany z lini poleceń. Zwróć uwagę na problem kodowania polskich znaków diakrytycznych.