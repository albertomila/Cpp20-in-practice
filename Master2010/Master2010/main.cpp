// Master2010.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <samples/S01/S01.casting.h>
#include <samples/S01/S01.foncteur.h>
#include <samples/S01/S01.singleton.h>
#include <samples/S01/S01.types.internes.h>
#include <samples/S02/GenSec2.h>
#include <samples/S02/GenSeq.h>
#include <samples/S02/S02.pimpl.h>
#include "samples/S04/S04.traits.h"
#include "samples/S04/S04.iterateurs.h"
#include "samples/S05/S05.Moyenne.h"
#include "samples/S06/S06.politiques.h"
#include "samples/S06/S06.TableauCollaborative.h"
#include "samples/S06/S06.TableauCollaborativeGenerique.h"
#include "samples/S06/S06.TableauInjection.h"
#include "samples/S06/S06.TableauLocale.h"
#include "samples/S06/S06.TableauMixim.h"
#include "samples/S06/S06.TableauPolymorphique.h"
#include "samples/S06/S06.TableauPolymorphique2.h"
#include "samples/S06/S06.TrucBartonNackman.h"
#include "samples/S07/S07.Referentiels.h"
#include "samples/S08/Allocation.h"
#include "samples/S08/Allocation2.h"
#include "samples/S11/S11.lexical_cast.h"
#include "samples/S11/S11.metaprogramation.h"
#include "samples/S11/S11.Selectur.Types.h"
#include "samples/S13/S13.Incompilable.h"
#include "samples/S13/S13.static_accumulate.h"
#include "samples/S13/S13.metaprogramation2.h"
#include "samples/S12/3rd version/principal.h"
#include "samples/S12/S12.pointeurs.de.fonctions.h"
#include "samples/S12/S12.methodes.instances.h"
#include "samples/S12/S12.composition.functions2.h"
#include "samples/S12/S12.composition.functions.h"
int main()
{
	Casting().Run();
	Functor().Run();
	SingletonTest().Run();
	InternalTypes().Run();
	GenSeq2Test().Run();
	GenSeqTest().Run();
	PImpl().Run();
	Traits().Run();
	Iterators().Run();
	Media().Run();
	Policies().Run();
	TableCollaborative().Run();
	TableGenericCollaborative().Run();
	TableInjection().Run();
	TableLocal().Run();
	TableMinimum().Run();
	TablePolimorphic().Run();
	TablePolimorphic2().Run();
	BartonNackman().Run();
	TemperatureTraits().Run();
	Allocation().Run();
	Allocation2().Run();
	LexicalCast().Run();
	Metaprogramming().Run();
	TypeSelector().Run();
	IncompilableTest().Run();
	StaticAccumulate().Run();
	Metaprogramming2().Run();
	Composite().Run();
	FunctionPointer().Run();
	InstanceMethods().Run();
	CompositionFunctions2().Run();
	CompositionFunctions().Run();
    return 0;
}

