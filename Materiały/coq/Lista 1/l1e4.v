Require Import Classical.

Lemma deMorgan_first : forall p q : Prop,
  ~(p /\ q) <-> ~p \/ ~q.
Proof.
split.
intros. 
apply NNPP; intro.
apply H.
split.
apply NNPP. intro. apply H0. left; assumption.
apply NNPP. intro. apply H0. right; assumption.
intros. intro. destruct H0. destruct H.
apply H; assumption.
apply H; assumption.
Qed.

Lemma deMorgan_second : forall p q : Prop,
  ~(p \/ q) <-> ~p /\ ~q.
Proof.
unfold not.
split.
intros.
split.
intro; apply H; left; assumption.
intro; apply H; right; assumption.
intros.
destruct H.
destruct H0.
apply H; assumption.
apply H1; assumption.
Qed.



