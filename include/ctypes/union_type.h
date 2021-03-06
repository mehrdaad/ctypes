/**
* @file include/ctypes/union_type.h
* @brief A representation of union types.
* @copyright (c) 2017 Avast Software, licensed under the MIT license
*/

#ifndef CTYPES_UNION_TYPE_H
#define CTYPES_UNION_TYPE_H

#include <memory>
#include <string>

#include "ctypes/composite_type.h"

namespace ctypes {

class Context;

/**
* @brief A representation of union types.
*/
class UnionType: public CompositeType
{
	public:
		static std::shared_ptr<UnionType> create(
			const std::shared_ptr<Context> &context,
			const std::string &name,
			const Members &members
		);

		virtual bool isUnion() const override;

		/// @name Visitor interface.
		/// @{
		virtual void accept(Visitor *v) override;
		/// @}

	private:
		// Instances are created by static method create().
		UnionType(const std::string &name, const Members &members);
};

} // namespace ctypes

#endif
