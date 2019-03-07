Section FirstTask.
Require Import Classical.

(* First *)
Goal forall A B : Prop, A -> (B -> A).
Proof.
intros.
assumption.
Qed.

(* Second *)
Goal forall A B C: Prop, (A->(B->C))->((A->B)->(A->C)).
Proof.
intros.
apply H. 
assumption.
apply H0.
assumption.
Qed.

(* Third *)
(* Classical *)
Goal forall A : Prop, (~A -> A) -> A.
Proof.
intros.
apply NNPP.
intro.
absurd A.
assumption.
apply H.
assumption.
Qed.

(* Forth *)
Goal forall A : Prop, A -> ~~A.
Proof.
intros.
intro.
absurd A.
assumption.
assumption.
Qed.

(* Fifth *)
(* Classical  *)
Goal forall A : Prop, ~~A -> A.
Proof.
intros.
apply NNPP.
assumption.
Qed.

(* Sixth *)
Goal forall A : Prop, ~~~A -> ~A.
Proof.
intros.
intro.
destruct H.
intro.
absurd A; assumption; assumption.
Qed.

(* Seventh: not true *)

(* Eighth *)
(* Classic *)
Goal forall A B : Prop, ~(A -> B) -> A.
Proof.
intros.
apply NNPP.
intro.
absurd A.
assumption.
destruct H.
intro.
absurd A; trivial.
Qed.

(* Ninth *)
Goal forall A B : Prop, ((((A -> B) -> A) -> A) -> B) -> B.
Proof.
intros.
apply H.
intro.
apply H0.
intro.
apply H.
intros.
assumption.
Qed.

(* Tenth *)
Goal forall A B C : Prop, (A -> B) -> (A -> ~B) -> A -> C.
Proof.
intros.
apply H in H1 as H2.
apply H0 in H1 as H3.
contradiction.
Qed.

End FirstTask.





