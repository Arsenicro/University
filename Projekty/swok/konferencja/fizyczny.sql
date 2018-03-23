--Model fizyczny na 2 czerwca

--o - organizator, u - uczestnik
CREATE DOMAIN rola AS varchar(1) CHECK (VALUE IN ('o','u')) NOT NULL;

CREATE DOMAIN ocena AS integer CHECK (VALUE BETWEEN 1 AND 10) NOT NULL;

--Status: p - propozycja, z-zaakceptowany, u-usunięty, d-dodatkowa flaga do całkowitego usunięcia z bazy
CREATE DOMAIN stat AS varchar(1) CHECK (VALUE IN ('p','z','u','d'));

--Kolejne tabele z modelu fizycznego

CREATE TABLE uczestnik (login text PRIMARY KEY, haslo text NOT NULL, uprawnienia rola NOT NULL DEFAULT 'u');

CREATE TABLE wydarzenie (nazwa text PRIMARY KEY, start timestamp NOT NULL, koniec timestamp CHECK (start < koniec) NOT NULL);

CREATE TABLE referat (id text PRIMARY KEY, prowadzacy text REFERENCES uczestnik (login), tytul text NOT NULL, poczatek timestamp NOT NULL, pokoj text, wydarzenie text, status stat NOT NULL);

CREATE TABLE zna (login_1 text REFERENCES uczestnik (login), login_2 text REFERENCES uczestnik (login));

CREATE TABLE propozycja_znajomosci (login_1 text REFERENCES uczestnik (login), login_2 text REFERENCES uczestnik (login));

CREATE TABLE zarejestrowal_sie (login_uczestnika text REFERENCES uczestnik (login), nazwa_wydarzenia text REFERENCES wydarzenie (nazwa));

CREATE TABLE uczestniczyl (login_uczestnika text REFERENCES uczestnik (login), id_referatu text REFERENCES referat (id));

CREATE TABLE ocenil (login_uczestnika text REFERENCES uczestnik (login), id_referatu text REFERENCES referat (id), ocena ocena);

--Funkcja kontrolująca proponowanie znajomości
--Jeśli się udało, sprawdza czy znajomość jest symetryczna
--Jeśli tak to usuwa z tabeli propozycja i dodaje do tabeli "zna"
--Zawiera też kontrolę błędów
CREATE OR REPLACE FUNCTION znajomosc() RETURNS TRIGGER AS $X$
	BEGIN
		IF NEW.login_1 = NEW.login_2 THEN
			RAISE EXCEPTION 'NIE MOZNA PROPONOWAC ZNAJOMOSCI SAMEMU SOBIE';
			RETURN NULL;
		END IF;
		IF EXISTS (SELECT * FROM propozycja_znajomosci WHERE login_1=NEW.login_2 AND login_2 = NEW.login_1) THEN
			INSERT INTO zna VALUES (NEW.login_1, NEW.login_2);
			DELETE FROM propozycja_znajomosci WHERE login_2 = NEW.login_1 AND login_1 = NEW.login_2;
			RETURN NULL;
		END IF;
		IF EXISTS (SELECT * FROM zna WHERE (login_1 = NEW.login_1 AND login_2 = NEW.login_2) OR (login_1 = NEW.login_2 AND login_2 = NEW.login_1))		THEN
			RAISE EXCEPTION 'UCZESTNICY JUŻ SIĘ ZNAJĄ';
			RETURN NULL;
		END IF;
		IF EXISTS (SELECT * FROM propozycja_znajomosci WHERE (login_1 = NEW.login_1 AND login_2 = NEW.login_2))	THEN
			RAISE EXCEPTION 'PROPOZYCJA ZNAJOMOSCI ISTNIEJE';
			RETURN NULL;
		END IF;
		RETURN NEW;
	END
$X$ LANGUAGE plpgsql;

CREATE TRIGGER symetryczna_znajomosc BEFORE INSERT ON propozycja_znajomosci FOR EACH ROW EXECUTE PROCEDURE znajomosc();

--Sprawdza czy wydarzenie istnieje i czy uzytkownik juz jest w tabeli
CREATE OR REPLACE FUNCTION zatwierdzanie_eventu() RETURNS TRIGGER AS $X$
	BEGIN
		IF NOT EXISTS(SELECT * FROM wydarzenie WHERE nazwa = NEW.nazwa_wydarzenia ) THEN
			RAISE EXCEPTION 'NIE MA TAKIEGO WYDARZENIA';
			RETURN NULL;
		END IF;
		IF EXISTS(SELECT * FROM zarejestrowal_sie WHERE nazwa_wydarzenia = NEW.nazwa_wydarzenia AND login_uczestnika = NEW.login_uczestnika) THEN
			RAISE EXCEPTION 'JEST JUZ ZAREJESTROWANY';
			RETURN NULL;
		END IF;
		RETURN NEW;
	END
$X$ LANGUAGE plpgsql;

--Zatwierdza uczestnictwo na wydarzeniu jeśli referat istnieje i jesli nie duplikujemy krotki
CREATE TRIGGER zatwierdz_rejestracje BEFORE INSERT ON zarejestrowal_sie FOR EACH ROW EXECUTE PROCEDURE zatwierdzanie_eventu();

--Sprawdza czy referat istnieje i czy uzytkownik juz jest w tabeli
CREATE OR REPLACE FUNCTION zatwierdzanie_referatu() RETURNS TRIGGER AS $X$
	BEGIN
		IF NOT EXISTS(SELECT * FROM referat WHERE id = NEW.id_referatu ) THEN
			RAISE EXCEPTION 'NIE MA TAKIEGO REFERATU';
			RETURN NULL;
		END IF;
		IF EXISTS(SELECT * FROM uczestniczyl WHERE id_referatu = NEW.id_referatu AND login_uczestnika = NEW.login_uczestnika) THEN
			RAISE EXCEPTION 'OBECNOSC ZOSTALA JUZ ODNOTOWANA';
			RETURN NULL;
		END IF;
		RETURN NEW;
	END
$X$ LANGUAGE plpgsql;

--Zatwierdza uczestnictwo na referacie jeśli referat istnieje i nie duplikujemy krotki
CREATE TRIGGER zatwierdz_uczestnictwo BEFORE INSERT ON uczestniczyl FOR EACH ROW EXECUTE PROCEDURE zatwierdzanie_referatu();

--Sprawdza czy referat istnieje i czy nie ma juz oceny tego wykladu tego uzytkownika
CREATE OR REPLACE FUNCTION zatwierdzenie_oceny() RETURNS TRIGGER AS $X$
	BEGIN
		IF NOT EXISTS(SELECT * FROM referat WHERE id = NEW.id_referatu ) THEN
			RAISE EXCEPTION 'NIE MA TAKIEGO REFERATU';
			RETURN NULL;
		END IF;
		IF EXISTS (SELECT * FROM ocenil WHERE login_uczestnika = NEW.login_uczestnika AND id_referatu = NEW.id_referatu) THEN
			RAISE EXCEPTION 'UZYTKOWNIK OCENIL JUZ TEN REFERAT';
			RETURN NULL;
		END IF;
		RETURN NEW;
	END
$X$ LANGUAGE plpgsql;

--Zatwierdza ocenę jeśli referat istnieje i to pierwszy wpis
CREATE TRIGGER zatwierdz_ocene BEFORE INSERT ON ocenil FOR EACH ROW EXECUTE PROCEDURE zatwierdzenie_oceny();


--Kolejne sytuacje:
--Jesli dodajemy nowy referat sprawdzamy czy istnieje takie wydarzenie. Jesli nie, i nie jest to pusty string, zwracamy blad.
--Jesli dodajemy nowy referat i wydarzenie istnieje, sprawdzamy czy poczatek zawiera sie w czasie wydarzenia
--Jesli nie ma prowadzacego o takim loginie zwracamy blad
--Jesli istnieje juz referat o takim id na liscie proponowanych aktualizujemy
--Wyglada na to, ze to wszystko (chyba)
--Przyjmuję konwencję, że jeśli id istnieje to aktualizujemy wszystko, nawet jeśli w propozycji było inaczej
CREATE OR REPLACE FUNCTION sprawdz_referat() RETURNS TRIGGER AS $X$
	DECLARE
	s timestamp;
	k timestamp;
	BEGIN
		IF NEW.status = 'z' THEN
			IF NOT EXISTS (SELECT * FROM wydarzenie WHERE nazwa = NEW.wydarzenie) THEN
				IF (NEW.wydarzenie) <> '' THEN
					RAISE EXCEPTION 'NIE MA TAKIEGO WYDARZENIA';
					RETURN NULL;
				END IF;
			ELSE
				SELECT start FROM wydarzenie WHERE nazwa=NEW.wydarzenie INTO s;
				SELECT koniec FROM wydarzenie WHERE nazwa=NEW.wydarzenie INTO k;
				IF (NEW.poczatek NOT BETWEEN s AND k) THEN
					RAISE EXCEPTION 'CZAS ROZPOCZECIA MUSI ZAWIERAC SIE POMIEDZY POCZATKIEM A KONCEM WYDARZENIA';
					RETURN NULL;
				END IF;
			END IF;
			IF NOT EXISTS (SELECT * FROM uczestnik WHERE login = NEW.prowadzacy) THEN
				RAISE EXCEPTION 'NIE MA UZYTKOWNIKA O TAKIM LOGINIE';
				RETURN NULL;
			END IF;
			IF EXISTS (SELECT * FROM referat WHERE id = NEW.id AND status='p') THEN
				UPDATE referat SET prowadzacy = NEW.prowadzacy, tytul = NEW.tytul, poczatek = NEW.poczatek, pokoj = NEW.pokoj, wydarzenie = NEW.wydarzenie, status = 'z' WHERE id = NEW.id;
				RETURN NULL;
			END IF;
		END IF;
		RETURN NEW;
	END
$X$ LANGUAGE plpgsql;

CREATE TRIGGER zatwierdz_referat BEFORE INSERT ON referat FOR EACH ROW EXECUTE PROCEDURE sprawdz_referat();

-- Wstawianie referatu. Konwencja: Wstawiam referat, wstawiam ocene zatwierdzajacego
CREATE OR REPLACE FUNCTION wstaw_referat(text,text,text,text,timestamp,text,ocena,text)
RETURNS VOID AS $X$
	INSERT INTO referat VALUES($3,$2,$4,$5,$6,$8,'z');
	INSERT INTO ocenil VALUES($1,$3,$7);
$X$ LANGUAGE SQL;

--Usuwanie referatu tzn zmiana flagi na u
CREATE OR REPLACE FUNCTION sprytnie_usun() RETURNS TRIGGER AS $X$
	BEGIN
		IF EXISTS(SELECT * FROM referat WHERE id = OLD.id AND status = 'p') THEN
			UPDATE referat SET status='u' WHERE id = OLD.id;
			RETURN NULL;
		END IF;
		IF EXISTS(SELECT * FROM referat WHERE id = OLD.id AND status = 'd') THEN
			RETURN OLD;
		END IF;
		RAISE EXCEPTION 'NIE MA TAKIEGO REFERATU NA LIŚCIE ZAPROPONOWANYCH';
		RETURN NULL;
	END
$X$ LANGUAGE plpgsql;

CREATE TRIGGER usun_propozycje BEFORE DELETE ON referat FOR EACH ROW EXECUTE PROCEDURE sprytnie_usun();

--Całkowicie usuwa referat używając specjalnej flagi
CREATE OR REPLACE FUNCTION calkowicie_usun_referat(text) RETURNS VOID AS $X$
	BEGIN
		UPDATE referat SET status='d' WHERE id=$1;
		DELETE FROM referat WHERE id=$1;
	END
$X$ LANGUAGE plpgsql;

--		insert_user
CREATE OR REPLACE FUNCTION wstaw_uczestnika(text,text,varchar(1)) RETURNS VOID AS $X$
	BEGIN
		INSERT INTO uczestnik VALUES ($1,$2,$3);
	END
$X$ LANGUAGE plpgsql;

--		register_event
CREATE OR REPLACE FUNCTION rejestracja_wydarzenia(text,timestamp,timestamp) RETURNS VOID AS $X$
	BEGIN
		INSERT INTO wydarzenie VALUES ($1,$2,$3);
	END
$X$ LANGUAGE plpgsql;

--		register_for_event
CREATE OR REPLACE FUNCTION rejestracja_na_wydarzenie(text,text) RETURNS VOID AS $X$
	BEGIN
		INSERT INTO zarejestrowal_sie VALUES ($1,$2);
	END
$X$ LANGUAGE plpgsql;

--		attendance
CREATE OR REPLACE FUNCTION odnotuj_obecnosc(text,text) RETURNS VOID AS $X$
	BEGIN
		INSERT INTO uczestniczyl VALUES ($1,$2);
	END
$X$ LANGUAGE plpgsql;

--		evaluation
CREATE OR REPLACE FUNCTION ocen_referat(text,text,integer) RETURNS VOID AS $X$
	BEGIN
		INSERT INTO ocenil VALUES ($1,$2,$3);
	END
$X$ LANGUAGE plpgsql;

--		reject
CREATE OR REPLACE FUNCTION odrzuc_referat(text) RETURNS VOID AS $X$
	BEGIN
		DELETE FROM referat WHERE id=$1;
	END
$X$ LANGUAGE plpgsql;

--		proposal
CREATE OR REPLACE FUNCTION proponuj_referat(text,text,text,timestamp) RETURNS VOID AS $X$
	BEGIN
		INSERT INTO referat(id,prowadzacy,tytul,poczatek,status) VALUES ($1,$2,$3,$4,'p');
	END
$X$ LANGUAGE plpgsql;

--		friend
CREATE OR REPLACE FUNCTION proponuj_znajomosc(text,text) RETURNS VOID AS $X$
	BEGIN
		INSERT INTO propozycja_znajomosci VALUES ($1,$2);
	END
$X$ LANGUAGE plpgsql;

--Funkcje które coś zwracają

--		user_plan
CREATE TYPE plan_uczestnika_typ AS 
(login text, 
talk text, 
start_timestamp timestamp,
title text,
room text);

--Zwraca z limitem jeśli limit jest podany
CREATE OR REPLACE FUNCTION plan(text, integer)
    RETURNS SETOF plan_uczestnika_typ AS $X$
    SELECT login_uczestnika, id, poczatek, tytul, pokoj FROM referat JOIN wydarzenie ON (wydarzenie=nazwa) JOIN zarejestrowal_sie ON (nazwa=nazwa_wydarzenia) WHERE login_uczestnika = $1 AND poczatek>=now() ORDER BY poczatek LIMIT $2;
$X$ LANGUAGE SQL;

CREATE OR REPLACE FUNCTION plan(text)
    RETURNS SETOF plan_uczestnika_typ AS $X$
    SELECT login_uczestnika, id, poczatek, tytul, pokoj FROM referat JOIN wydarzenie ON (wydarzenie=nazwa) JOIN zarejestrowal_sie ON (nazwa=nazwa_wydarzenia) WHERE login_uczestnika = $1 AND status = 'z' AND poczatek>=now() ORDER BY poczatek;
$X$ LANGUAGE SQL;

--		day_plan
CREATE TYPE plan_dnia_typ AS 
(talk text, 
start_timestamp timestamp,
title text,
room text);

CREATE OR REPLACE FUNCTION plan_dnia(timestamp)
    RETURNS SETOF plan_dnia_typ AS $X$
    SELECT id, poczatek, tytul, pokoj FROM referat WHERE poczatek::date = $1 AND status = 'z' ORDER BY pokoj, poczatek;
$X$ LANGUAGE SQL;


--		best_talks
CREATE TYPE plan_dnia_pomocniczy_typ AS 
(talk text, 
start_timestamp timestamp,
title text,
room text,
ocena ocena);

--Przyjęte założenie: organizator nie jest uczestnikiem. 
--Dzięki temu wypisanie oceny organizatora który ocenił dany referat daje nam pewność, że jest to ocena początkowa
--Zuniowanie jej z wszystkimi którzy byli na wykładzie pozwala na wykonanie zapytania best_talks w którym atrybut all jest różny od 1
-- (Ocena początkowa liczy się jak ocena obecnego na wykładzie)
CREATE OR REPLACE FUNCTION najlepsze_referaty_pomocnicze(timestamp,timestamp)
    RETURNS SETOF plan_dnia_pomocniczy_typ AS $X$
	((SELECT id,poczatek,tytul,pokoj,ocena FROM 
		referat
		JOIN uczestniczyl u ON(id_referatu = id) 
		JOIN ocenil o ON(o.id_referatu = id AND o.login_uczestnika = u.login_uczestnika)
		WHERE (poczatek BETWEEN $1 AND $2)
		AND status='z')
		UNION
	(SELECT id,poczatek,tytul,pokoj,ocena FROM referat JOIN ocenil ON(id_referatu = id) JOIN uczestnik ON(login=login_uczestnika) WHERE (poczatek BETWEEN $1 AND $2) AND (uprawnienia = 'o') AND status='z'))
$X$ LANGUAGE SQL;

--Zależnie od argumentów obsługuje sytuacje zawarte w treści:
--najlepsze_referaty są dla all<>1
--wszystkie_najlepsze_referaty są dla all = 1
CREATE OR REPLACE FUNCTION najlepsze_referaty(timestamp,timestamp)
    RETURNS SETOF plan_dnia_typ AS $X$
		SELECT talk,start_timestamp,title,room FROM najlepsze_referaty_pomocnicze($1,$2)
		GROUP BY talk,start_timestamp,title,room 
		ORDER BY AVG(ocena) DESC;
$X$ LANGUAGE SQL;

CREATE OR REPLACE FUNCTION najlepsze_referaty(timestamp,timestamp,integer)
    RETURNS SETOF plan_dnia_typ AS $X$
		SELECT talk,start_timestamp,title,room FROM najlepsze_referaty_pomocnicze($1,$2)
		GROUP BY talk,start_timestamp,title,room 
		ORDER BY AVG(ocena) DESC
		LIMIT $3;
$X$ LANGUAGE SQL;

CREATE OR REPLACE FUNCTION wszystkie_najlepsze_referaty(timestamp,timestamp)
    RETURNS SETOF plan_dnia_typ AS $X$
    SELECT id_referatu,poczatek,tytul,pokoj FROM referat JOIN ocenil ON(id=id_referatu) 
		WHERE (poczatek BETWEEN $1 AND $2) 
		AND status='z'
		GROUP BY id_referatu,poczatek,tytul,pokoj 
		ORDER BY AVG(ocena) DESC;
$X$ LANGUAGE SQL;

CREATE OR REPLACE FUNCTION wszystkie_najlepsze_referaty(timestamp,timestamp,integer)
    RETURNS SETOF plan_dnia_typ AS $X$
    SELECT id_referatu,poczatek,tytul,pokoj FROM referat JOIN ocenil ON(id=id_referatu) 
		WHERE (poczatek BETWEEN $1 AND $2)
		AND status='z'
		GROUP BY id_referatu,poczatek,tytul,pokoj 
		ORDER BY AVG(ocena) DESC
		LIMIT $3;
$X$ LANGUAGE SQL;

--		most_popular_talk
CREATE OR REPLACE FUNCTION najpopularniejsze_referaty(timestamp,timestamp)
    RETURNS SETOF plan_dnia_typ AS $X$
    SELECT id_referatu,poczatek,tytul,pokoj FROM 
	referat JOIN uczestniczyl ON(id=id_referatu) 
	WHERE poczatek BETWEEN $1 AND $2 
	AND status = 'z'
	GROUP BY id_referatu,poczatek,tytul,pokoj
	ORDER BY COUNT(distinct login_uczestnika) DESC;
$X$ LANGUAGE SQL;

CREATE OR REPLACE FUNCTION najpopularniejsze_referaty(timestamp,timestamp,integer)
    RETURNS SETOF plan_dnia_typ AS $X$
    SELECT id_referatu,poczatek,tytul,pokoj FROM 
	referat JOIN uczestniczyl ON(id=id_referatu) 
	WHERE poczatek BETWEEN $1 AND $2 
	AND status = 'z'
	GROUP BY id_referatu,poczatek,tytul,pokoj
	ORDER BY COUNT(distinct login_uczestnika) DESC
	LIMIT $3;
$X$ LANGUAGE SQL;

--		attended_talks
CREATE OR REPLACE FUNCTION referaty_uczestnika(text)
    RETURNS SETOF plan_dnia_typ AS $X$
    SELECT id_referatu, poczatek, tytul, pokoj FROM uczestniczyl JOIN referat ON(id_referatu = id) WHERE login_uczestnika =$1 AND status = 'z';
$X$ LANGUAGE SQL;

CREATE OR REPLACE FUNCTION referaty_uczestnika(text,integer)
    RETURNS SETOF plan_dnia_typ AS $X$
    SELECT id_referatu, poczatek, tytul, pokoj FROM uczestniczyl JOIN referat ON(id_referatu = id) WHERE login_uczestnika =$1 AND status = 'z'
	LIMIT $2;
$X$ LANGUAGE SQL;


--		abandoned_talks
CREATE TYPE porzucone_referaty_typ AS 
(talk text, 
start_timestamp timestamp,
title text,
room text,
number integer);

--Zwraca liczbę osób których nie było na referacie o id $1 choć były zapisane na wydarzenie
CREATE OR REPLACE FUNCTION liczba_nieuczestniczacych(text)
	RETURNS integer AS $X$
	DECLARE 
		n text;
		i integer;
	BEGIN
		SELECT wydarzenie FROM referat WHERE id = $1 INTO n;
		SELECT COUNT(*) FROM (
		(SELECT login_uczestnika FROM zarejestrowal_sie WHERE nazwa_wydarzenia = n)
		EXCEPT
		(SELECT login_uczestnika FROM uczestniczyl WHERE id_referatu = $1)) AS x INTO i;
		RETURN i;
	END
$X$ LANGUAGE plpgsql;

--Wykonuje zaptanie
CREATE OR REPLACE FUNCTION porzucone_referaty_pomocnicze()
	RETURNS SETOF porzucone_referaty_typ AS $X$
	DECLARE 
		i text;
		n porzucone_referaty_typ;
	BEGIN
		FOR i IN (SELECT id FROM referat WHERE status = 'z')
	LOOP
		SELECT id,poczatek,tytul,pokoj FROM referat WHERE id=i AND status='z' INTO n;
		n.number = liczba_nieuczestniczacych(i);
		RETURN NEXT n;
	END LOOP;
	END
$X$ LANGUAGE plpgsql;

--Dba tylko o kolejność
CREATE OR REPLACE FUNCTION porzucone_referaty()
    RETURNS SETOF porzucone_referaty_typ AS $X$
    SELECT * FROM porzucone_referaty_pomocnicze() ORDER BY number DESC;
$X$ LANGUAGE SQL;

CREATE OR REPLACE FUNCTION porzucone_referaty(integer)
    RETURNS SETOF porzucone_referaty_typ AS $X$
	SELECT * FROM porzucone_referaty_pomocnicze() ORDER BY number DESC LIMIT $1;
$X$ LANGUAGE SQL;

--		Funkcje do rejected_talks
CREATE TYPE referaty_typ AS 
(talk text, 
speakerlogin text,
start_timestamp timestamp,
title text);

--Dla organizatora
CREATE OR REPLACE FUNCTION wszystkie_odrzucone()
	RETURNS SETOF referaty_typ AS $X$
	SELECT id, prowadzacy, poczatek, tytul FROM referat WHERE status = 'u';
$X$ LANGUAGE SQL;

--Dla uczesnika
CREATE OR REPLACE FUNCTION moje_odrzucone(text)
	RETURNS SETOF referaty_typ AS $X$
	SELECT id, prowadzacy, poczatek, tytul FROM referat WHERE status = 'u' AND prowadzacy = $1;
$X$ LANGUAGE SQL;

--		proposals
CREATE OR REPLACE FUNCTION propozycje()
	RETURNS SETOF referaty_typ AS $X$
	SELECT id, prowadzacy, poczatek, tytul FROM referat WHERE status = 'p';
$X$ LANGUAGE SQL;

--Zwraca znajonych uczestnika o loginie $1
CREATE OR REPLACE FUNCTION znajomi(text)
	RETURNS SETOF text AS $X$
	(SELECT login FROM zna JOIN uczestnik ON(login=login_1) WHERE login_2 = $1) UNION (SELECT login FROM zna JOIN uczestnik ON(login=login_2) WHERE login_1=$1);
$X$ LANGUAGE SQL;

--		friends_talk
CREATE TYPE referaty_znajomych_typ AS 
(talk text, 
speakerlogin text,
start_timestamp timestamp,
title text,
room text);

CREATE OR REPLACE FUNCTION referaty_znajomych(text, timestamp, timestamp)
	RETURNS SETOF referaty_znajomych_typ AS $X$
	SELECT id,prowadzacy,poczatek,tytul,pokoj FROM referat 
	JOIN znajomi($1) ON (znajomi=prowadzacy) 
	AND poczatek BETWEEN $2 AND $3
	AND status = 'z'
	ORDER BY poczatek
$X$ LANGUAGE SQL;

CREATE OR REPLACE FUNCTION referaty_znajomych(text, timestamp, timestamp, integer)
	RETURNS SETOF referaty_znajomych_typ AS $X$
	SELECT id,prowadzacy,poczatek,tytul,pokoj FROM referat 
	JOIN znajomi($1) ON (znajomi=prowadzacy) 
	AND poczatek BETWEEN $2 AND $3
	AND status = 'z'
	ORDER BY poczatek
	LIMIT $4;
$X$ LANGUAGE SQL;

--		friends_event
CREATE TYPE znajomi_na_wydarzeniach_typ AS 
(login text, 
_event text,
friendlogin text);

CREATE OR REPLACE FUNCTION znajomi_na_wydarzeniach(text, text)
	RETURNS SETOF znajomi_na_wydarzeniach_typ AS $X$
	SELECT $1,nazwa_wydarzenia,login_uczestnika FROM zarejestrowal_sie 
	JOIN znajomi($1) ON (login_uczestnika = znajomi)
	WHERE (nazwa_wydarzenia = $2);
$X$ LANGUAGE SQL;