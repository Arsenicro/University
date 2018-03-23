# Projektowanie i implementacja zaawansowanych aplikacji PHP

## REST API


### Zadanie

Zaprojektuj, a następnie zaimplementuj z wykorzystaniem mikroframeworka Silex REST API do obsługi prostego katalogu produktów. API powinno udostępniać następujące metody:

- GET /products
    - zwraca reprezentację wszystkich produktów (id, nazwa)
    - dane zwracane są w formacie JSON
- POST /products
    - dodaje nowy produkt do katalogu
- GET /products/{id}
    - zawraca reprezentację produktu o podanym id (wszystkie właściwości)
    - dane zwracane są w formacie JSON 
- PUT /products/{id}
    - nadpisuje produkt o podanym id
- DELETE /products/{id} 
    - usuwa produkt o podanym id

gdzie:

- id jest dodatnią liczą całkowitą
- produkt jest opisany przez:
    - id (int), nadawany przez serwer kolejny (lub losowy) unikalny identyfikator
    - nazwę (string)
    - cenę (Money)
- dane produktów składowane są w osobnych plikach, ze względów bezpieczeństwa katalog z danymi powinien znajdować się poza obszarem dostępnym poprzez HTTP


### Uwagi

Program będzie uruchamiany z lini poleceń, przy wykorzystaniu wbudowanego serwera developerskiego HTTP. Przygotuj instrukcję konsolową do jego uruchomienia. 


### Wskazówki

- [Metody HTTP w kontekście usług REST](http://www.restapitutorial.com/lessons/httpmethods.html)
- Zapis i odczyt plików z filesystemu można zrealizować na wiele sposobów:
    - mechanizmy wbudowane
        - [file_put_contents](http://php.net/manual/en/function.file-put-contents.php)
        - [file_get_contents](http://php.net/manual/en/function.file-get-contents.php)
    - abstrakcje ponad systemem plików
        - [Gaufrette, Githu](https://github.com/KnpLabs/Gaufrette)
        - [Gaufrette, dokumentacja, przykładowe użycie](https://knplabs.github.io/Gaufrette/basic-usage.html)
- API można testować bezpośrednio z poziomu przelądarki, ale developer aplikacji webowych powinien być zaznajomiony z dedykowanymi narzędziami, np.:
    - [Insomnia](https://insomnia.rest)
    - [Postman](https://www.getpostman.com)