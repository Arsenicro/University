Parameter man : Set.
Parameter barber : man -> Prop.
Parameter shave : man -> man -> Prop.

Axiom text :
forall x : man, barber x -> 
(
(forall y, (~shave y y) -> shave x y)
/\
(forall y, shave y y -> (~shave x y))
).

Goal ~exists x : man, barber x.
Proof.
intro.
destruct H.
assert (forall x : man, barber x -> ((forall y, ~shave y y -> shave x y) /\ (forall y, shave y y -> ~shave x y))).
apply text.
destruct (H0 x).
assumption.
absurd (shave x x).
intro.
absurd (shave x x).
apply H2.
assumption.
assumption.
apply H1.
intro.
absurd (shave x x).
apply H2.
assumption.
assumption.
Qed.