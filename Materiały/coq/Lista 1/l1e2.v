Require Import Classical.

Parameter S T : Set.
Parameter A : S -> T -> Prop.
Parameter B : T -> Prop.
Parameter C : Prop.

(* First: not true *)

(* Second *)
(* Non-constructive *)
Goal (~forall x, B x) -> exists x, ~ B x.
Proof.
intros.
apply NNPP.
intro.
apply H.
intro.
apply NNPP.
intro.
apply H0.
exists x.
assumption.
Qed.

(* Third *)
Goal (exists x, ~ B x) -> ~ (forall x, B x).
Proof.
intros.
intro.
destruct H.
apply H.
apply H0.
Qed.

(* Forth *)
Goal ~(exists x, B x) -> (forall x, ~B x).
Proof.
intros.
intro.
destruct H.
exists x.
apply H0.
Qed.

(* Fifth *)
Goal (forall x, ~B x) -> (~exists x, B x).
Proof.
intros.
intro.
destruct H0.
apply (H x).
assumption.
Qed.

(* Sixth: not true (empty set) *)

(* Seventh *)
Goal (exists x, (C -> B x)) -> C -> exists x, B x.
Proof.
intros.
destruct H.
exists x.
apply H.
assumption.
Qed.

(* Eighth: not true (empty set) *)