#pragma once
#include "stdafx.h"
#include "samples/S12/3rd version/functional_extension.h"
#include <functional>

template <class FX, class GX>
   class compose2_fx_gx_impl
      : public std::unary_function<
           typename unary_function_traits<GX>::argument_type,
           typename unary_function_traits<FX>::result_type
        >
   {
      FX fx_;
      GX gx_;
   public:
      compose2_fx_gx_impl (FX fx, GX gx)
         : fx_(fx), gx_(gx)
      {
      }
      result_type operator()(argument_type arg)
      { 
		  return fx_(gx_(arg)); 
	  }
	  template <class T>
		T to_();

	  template <>
		  FX to_<FX>()
		  { 
			  return fx_; 
		  }

	  template <>
		  GX to_<GX>()
		  { 
			  return gx_; 
		  }
   };

template <class FX, class GX>
	compose2_fx_gx_impl<FX, GX> compose2_fx_gx (FX fx, GX gx)
	{ 
		return compose2_fx_gx_impl<FX, GX> (fx, gx); 
	}

template <
	template <class,class> class Comp,
	class FX, 
	class GX
>
	FX extract_first (Comp<FX,GX> fct)
	{ 
		return fct.to_<FX>(); 
	}