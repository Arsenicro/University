Parameter things beings: Set.
Parameter member : beings -> Prop.
Parameter Sesshomaru Naraku Inuyasha : beings.
Parameter likes : beings -> things -> Prop.
Parameter snow rain: things.
Parameter human demon: beings -> Prop.

Axiom Sesshomaru_in_sect:
member Sesshomaru.
Axiom Naraku_in_sect:
member Naraku.
Axiom Inuyasha_in_sect:
member Inuyasha.

Axiom member_is_demon_or_human :
forall x: beings, member x -> (human x \/ demon x).

Axiom humans_dont_like_rain :
forall x: beings, human x -> ~likes x rain.

Axiom demons_like_snow :
forall x: beings, demon x -> likes x snow.

Axiom naraku_dont_like_what_sesshomaru_does :
forall x: things, likes Sesshomaru x -> ~likes Naraku x.

Axiom naraku_likes_what_sesshomaru_dont : 
forall x: things, ~likes Sesshomaru x -> likes Naraku x.

Axiom sesshomaru_likes_snow :
likes Sesshomaru snow.

Axiom sesshomaru_likes_rain :
likes Sesshomaru rain.

(* Lemmas *)

Lemma sesshomaru_is_not_human : 
~human Sesshomaru.
Proof.
intro.
assert (forall x: beings, human x -> ~likes x rain).
apply humans_dont_like_rain.
apply (H0 Sesshomaru).
assumption.
apply sesshomaru_likes_rain.
Qed.

Lemma naraku_dont_like_snow :
~likes Naraku snow.
Proof.
assert (likes Sesshomaru snow).
apply sesshomaru_likes_snow.
assert (forall x: things, likes Sesshomaru x -> ~likes Naraku x).
apply naraku_dont_like_what_sesshomaru_does.
apply (H0 snow).
assumption.
Qed.

Lemma naraku_is_not_demon:
~demon Naraku.
Proof.
intro.
assert (forall x: beings, demon x -> likes x snow). 
apply demons_like_snow.
absurd (likes Naraku snow).
apply naraku_dont_like_snow.
apply (H0 Naraku).
assumption.
Qed.

Lemma naraku_is_human :
human Naraku.
Proof.
assert (member Naraku).
apply Naraku_in_sect.
assert (human Naraku \/ demon Naraku).
assert (forall x: beings, member x -> (human x \/ demon x)).
apply member_is_demon_or_human.
apply H0; assumption.
destruct H0.
assumption.
absurd (demon Naraku).
apply naraku_is_not_demon.
assumption.
Qed.


(* And big finish *)

Goal exists x : beings, human x /\ ~demon x.
Proof.
assert (human Naraku /\ ~demon Naraku).
split.
apply naraku_is_human.
apply naraku_is_not_demon.
exists Naraku.
assumption.
Qed.