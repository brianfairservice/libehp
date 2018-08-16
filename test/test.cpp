/*
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
*/


#include <ehp.hpp>
#include <iostream>
#include <assert.h>

using namespace std;
using namespace EHP;

void usage(int argc, char* argv[])
{
	cout<<"Usage: "<<argv[0]<<" <program to print eh info>"<<endl;
	exit(1);
}



void print_lps(const EHFrameParser_t* ehp)
{
	const auto fdes=ehp->getFDEs();
	cout<<hex;
	for(const auto fde : *fdes)
	{
		cout<<"Found FDE at : " << fde->getStartAddress() << "-"<<fde->getEndAddress()<<endl;
		const auto lsda=fde->getLSDA();
		assert(lsda);
		const auto callsites=lsda->getCallSites();
		assert(callsites);

		for(const auto cs : *callsites)
		{
			cout<<"\tCall site (0x"<<cs->getCallSiteAddress()<<"-"<<cs->getCallSiteEndAddress()
			    <<") with landing pad=0x"<<cs->getLandingPadAddress()<<endl;
		}
	}
	cout<<dec;
}

int main(int argc, char* argv[])
{

	if(argc!=2)
	{
		usage(argc,argv);
	}

	auto ehp = EHFrameParser_t::factory(argv[1]);
	ehp->print();


	print_lps(ehp.get());

	return 0;
}
