






















































































































































































		cout << "moving job to fail machine '" << fail << "'\n";
		for(auto &m2 : machineList) {
			if(m2.getTaskName() == fail) {
				m2.AddJob(job);
				break;
			}
		}
	};
	
	if(! didSomething) {
		//
		MovePass();
		continue;
	}
	
	if(m.getTaskFail.empty()){
		//
		MovePass();
		continue;
	}
	
	//
	if(rand() & 1){
	
	
		MovePass();
		
	}
	