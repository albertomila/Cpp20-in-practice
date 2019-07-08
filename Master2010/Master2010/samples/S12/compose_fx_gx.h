#pragma once
#include "stdafx.h"
#include "samples/S12/3rd version/functional_extension.h"
#include <functional>
using std::unary_function;

template <class FX, class GX>
class compose_fx_gx_impl
    : public std::unary_function<
        typename unary_function_traits<GX>::argument_type,
        typename unary_function_traits<FX>::result_type
    >
{
    FX fx_;
    GX gx_;
public:
    compose_fx_gx_impl(FX fx, GX gx)
        : fx_(fx), gx_(gx)
    {
    }
    result_type operator()(argument_type arg)
    { 
		return fx_(gx_(arg)); 
	}
};

template <class FX, class GX>
compose_fx_gx_impl<FX, GX> compose_fx_gx(FX fx, GX gx)
{ 
	return compose_fx_gx_impl<FX, GX>(fx, gx); 
}