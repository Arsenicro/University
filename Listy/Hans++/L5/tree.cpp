#include "tree.h"

tree::~tree() {
    pntr->refcnt--;
    if(pntr->refcnt == 0) delete pntr;
}

//4.


std::ostream& operator << ( std::ostream& stream, const tree& t )
{ 
	stream<<t.functor()<<'(';
	for(size_t i = 0; i < t.nr_subtrees(); ++i)  
		stream << t[i] << ",";
	stream<<t.functor()<<")";	
	return stream;
}


//5.

void tree::ensure_not_shared() {
	if (pntr->refcnt != 1) {
		pntr->refcnt--;
		pntr = new trnode(pntr->f, pntr->subtrees, 1);
	}
}
#if 0
string& tree::functor() {
	ensure_not_shared();
	return pntr->f;
}

tree& tree::operator[] (size_t i) {
	ensure_not_shared();
	return pntr->subtrees[i];
}

#endif

//6

#if 0
tree subst( const tree& t, const string& var, const tree& val ){
	tree res = t;	
	if(res.nr_subtrees() == 0){
		if(res.functor() == var) return val;
		else return res;
	}
	for(size_t i = 0; i<t.nr_subtrees(); i++){
		if(res[i].functor() == var && res[i].nr_subtrees() == 0){
			res[i]=val;
		}else{
			res[i]=subst(res[i],var,val);
		}
	}
	
	return res;
}
#endif

//7.
void tree::replacesubtree( size_t i, const tree& t ) {
	if (pntr->subtrees[i].pntr != t.pntr) {
		ensure_not_shared();
		pntr->subtrees[i] = t;
	}
}

void tree::replacefunctor( const string& f ) {
	if(pntr->f != f){
		ensure_not_shared();
		pntr->f = f;
	}
}

//8.
#if 1
tree subst( const tree& t, const string& var, const tree& val ){
	tree res = t;	
	if (res.functor() == var && t.nr_subtrees() == 0) {		
		return val;
	}
	for (size_t i = 0; i < res.nr_subtrees(); i++) {
		res.replacesubtree(i, subst(res[i], var, val));
	}

	return res;
}

#endif

