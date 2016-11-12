bool conjunto::insert(const conjunto::entrada & e) {

    bool inserta = false;
    conjunto::iterator it;
    it.itv = this->vc.begin();

    conjunto::iterator it_final;
    it_final.itv = this->vc.end();

    conjunto::iterator it_find;
    it_find = this->find(e.getID());
	
	

    if (it_find == it_final) {

     while (it != it_final && !inserta) {
          if ((*it).getID() > e.getID()) {
              this->vc.insert((it.itv), e);
              insertado = true;
          } else
              it++;
     }
     }
    
	if (!inserta){
		inserta = true;
		this->vc.push_back (e);
	} 
    return inserta;
    
}
