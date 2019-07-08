#pragma once
#include "stdafx.h"

#include "functional_extension.h"
#include "composite_function_traits.h"
#include "samples/S11/S11.metaprogramation.h"

#pragma warning (disable : 4101)
template <class FX, class GX>
   class compose3_fx_gx_impl
      : public std::unary_function<
           typename unary_function_traits<GX>::argument_type,
           typename unary_function_traits<FX>::result_type
        >
   {
      FX fx_;
      GX gx_;
   public:
      compose3_fx_gx_impl (FX fx, GX gx)
         : fx_(fx), gx_(gx)
      {
      }
      result_type operator()(argument_type arg)
         { return fx_(gx_(arg)); }
      template <class T>
         T to_()
         {
			 static_assert_<
				 possesses_function<
					  compose3_fx_gx_impl<FX,GX>, T
				   >::VAL
			 > IndirectionIllegale;
			 /*
            static_assert_<
               possesses_function<
                  compose3_fx_gx_impl<FX,GX>, T
               >::VAL
            > IndirectionIllegale;
			*/
            return to_<
               typename composite_function_child_selector<
                  FX,GX,T
               >::type
            >().to_<T>();
         }
      template <>
         FX to_<FX>()
            { return fx_; }
      template <>
         GX to_<GX>()
            { return gx_; }
   };
#pragma warning (default : 4101)

template <class FX, class GX>
compose3_fx_gx_impl<FX, GX> compose3_fx_gx(FX fx, GX gx)
{
	return compose3_fx_gx_impl<FX, GX>(fx, gx);
}
