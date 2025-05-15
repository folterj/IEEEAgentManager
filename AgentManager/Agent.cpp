#include "StdAfx.h"
#include "Agent.h"
#include "phd_constants.h"

Agent::Agent(AMModelInterface^ model0,ComInterface^ com0,UInt64 eui0,String^ spec0)
	: AMApp(model0,com0,eui0,spec0)
{
	actions = gcnew array<array<int>^> {
/*	NoChange		*/ {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0	},

/*						0	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15	16	17	18	19	20	21	22	23	24	25	26	27	28	29	30	31	32	33	34	/*
/*							Ind	Ind	Ind	Ind	Req	Req	Req	Rx	Req	Req	Req	Rx	Rx	Rx	Rx	Rx	Rx	Rx	Rx	Req	Rx	Rx	Rx	Rx	Rx	Rx	Rx	Rx	Rx	Rx	Req	Req	Ind	Req	*/
/*							Tra	Tra	Tim	Tim	Ass	Ass	Ass	Aa	Cnf	Cnf	Cnf	Aa	Are	Are	Are	Rl	Rl	Ab	Apd	Cnf	Rov	Rov	Rov	Rov	Rov	Ror	Ror	Ror	Ror	Ror	Cnf	Cnf	App	Rov	*/
/*							Con	Dis		Max		Rel	Ab	rq	Ac	Unk	Rej	re	Ac	Unk	Rej	rq	re		Oth	Evt		Mds	NMd	Evt	Oth	Roe	Add	Uns	Acc	Oth	Uns	Sup	Evt	Oth	*/
/*1	Disconnected	*/ {0,	OK,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0	},
/*2	Unassociated	*/ {0,	0,	OK,	0,	0,	AS,	OK,	SAB,OK,	0,	0,	0,	AB,	0,	0,	0,	AB,	0,	0,	AB,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0	},
/*3	Associating		*/ {0,	0,	OK,	AS,	SAR,0,	SAB,SAB,OK,	0,	0,	0,	0,	OK,	OK,	OK,	AB,	AB,	OK,	AB,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0	},
/*4	Config_Sending	*/ {0,	0,	OK,	0,	SAR,0,	DIS,SAB,AB,	0,	0,	0,	AB,	0,	0,	0,	OK,	AB,	OK,	AB,	0,	0,	OK,	ERR,0,	0,	AB,	0,	0,	0,	0,	0,	CFG,0,	0	},
/*5	Config_Checking	*/ {0,	0,	OK,	0,	SAC,0,	DIS,SAB,AB,	0,	0,	0,	AB,	0,	0,	0,	OK,	AB,	OK,	AB,	0,	0,	OK,	ERR,0,	0,	0,	OK,	DIS,OK,	AB,	0,	0,	0,	0	},
/*6	Operating		*/ {0,	0,	OK,	0,	SAR,0,	DIS,SAB,AB,	0,	0,	0,	AB,	0,	0,	0,	OK,	AB,	OK,	AB,	0,	OK,	0,	0,	0,	0,	OK,	0,	0,	0,	0,	0,	0,	0,	0	},
/*7	Disassociating	*/ {0,	0,	OK,	0,	SAR,0,	0,	SAB,AB,	0,	0,	0,	AB,	0,	0,	0,	OK,	OK,	OK,	AB,	0,	0,	0,	0,	0,	0,	AB,	0,	0,	0,	0,	0,	0,	0,	0	}
	};

	newStates = gcnew array<array<int>^> {
/*	NoChange		*/ {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0	},

/*						0	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15	16	17	18	19	20	21	22	23	24	25	26	27	28	29	30	31	32	33	34	/*
/*							Ind	Ind	Ind	Ind	Req	Req	Req	Rx	Req	Req	Req	Rx	Rx	Rx	Rx	Rx	Rx	Rx	Rx	Req	Rx	Rx	Rx	Rx	Rx	Rx	Rx	Rx	Rx	Rx	Req	Req	Ind	Req	*/
/*							Tra	Tra	Tim	Tim	Ass	Ass	Ass	Aa	Cnf	Cnf	Cnf	Aa	Are	Are	Are	Rl	Rl	Ab	Apd	Cnf	Rov	Rov	Rov	Rov	Rov	Ror	Ror	Ror	Ror	Ror	Cnf	Cnf	App	Rov	*/
/*							Con	Dis		Max		Rel	Ab	rq	Ac	Unk	Rej	re	Ac	Unk	Rej	rq	re		Oth	Evt		Mds	NMd	Evt	Oth	Roe	Add	Uns	Acc	Oth	Uns	Sup	Evt	Oth	*/
/*1	Disconnected	*/ {0,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0	},
/*2	Unassociated	*/ {0,	0,	1,	0,	0,	3,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0	},
/*3	Associating		*/ {0,	0,	1,	0,	2,	0,	2,	2,	2,	0,	0,	0,	0,	6,	4,	2,	2,	2,	2,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0	},
/*4	Config_Sending	*/ {0,	0,	1,	0,	2,	0,	7,	2,	2,	0,	0,	0,	2,	0,	0,	0,	2,	2,	2,	2,	0,	0,	0,	0,	0,	0,	2,	0,	0,	0,	0,	0,	5,	0,	0	},
/*5	Config_Checking	*/ {0,	0,	1,	0,	2,	0,	7,	2,	2,	0,	0,	0,	2,	0,	0,	0,	2,	2,	2,	2,	0,	0,	0,	0,	0,	0,	0,	4,	7,	6,	2,	0,	0,	0,	0	},
/*6	Operating		*/ {0,	0,	1,	0,	2,	0,	7,	2,	2,	0,	0,	0,	2,	0,	0,	0,	2,	2,	2,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0	},
/*7	Disassociating	*/ {0,	0,	1,	0,	2,	0,	0,	2,	2,	0,	0,	0,	2,	0,	0,	0,	0,	2,	2,	2,	0,	0,	0,	0,	0,	0,	2,	0,	0,	0,	0,	0,	0,	0,	0	}
	};

	switch (specType) {
		case SpecType::Scales:			devSpec = gcnew ScalesSpec(eui);								break;
		case SpecType::BloodPressure:	devSpec = gcnew BloodPressureSpec(eui);							break;
		case SpecType::BloodGlucose:	devSpec = gcnew BloodGlucoseSpec(eui);							break;
		case SpecType::PulseOxim:		devSpec = gcnew PulseOximSpec(eui);								break;
		case SpecType::Motion:			devSpec = gcnew MotionSpec(eui);								break;
		case SpecType::Usage:			devSpec = gcnew UsageSpec(eui);									break;
		default:						devSpec = gcnew DevSpec(specType,EXTENDED_CONFIG_START,eui);	break;
	}

	connected();
}

void Agent::connected()
{
	isconnected = true;
	state = AMState::Unassociated;
	model->updateSpec(eui,spec,getState(),ComCommand::Connect);
	// start association
	handleEvent(AMEvent::Req_Assoc);
}

void Agent::disconnected()
{
	isconnected = false;
	state = AMState::Disconnected;
	model->updateSpec(eui,spec,getState(),ComCommand::Disconnect);
}
