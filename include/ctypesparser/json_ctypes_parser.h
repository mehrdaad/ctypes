/**
* @file include/ctypesparser/json_ctypes_parser.h
* @brief Parser for C-types from JSON files.
* @copyright (c) 2017 Avast Software, licensed under the MIT license
*/

#ifndef CTYPESPARSER_JSON_CTYPES_PARSER_H
#define CTYPESPARSER_JSON_CTYPES_PARSER_H

#include <functional>
#include <string>
#include <unordered_map>

#include <rapidjson/document.h>

#include "ctypesparser/ctypes_parser.h"

namespace ctypesparser {

/**
* @brief Parser for C-types represented in JSON.
*/
class JSONCTypesParser: public CTypesParser
{
	public:
		JSONCTypesParser();
		JSONCTypesParser(unsigned defaultBitWidth);

		virtual std::unique_ptr<ctypes::Module> parse(
			std::istream &stream,
			const TypeWidths &typeWidths = {},
			const ctypes::CallConvention &callConvention = ctypes::CallConvention()) override;
		virtual void parseInto(
			std::istream &stream,
			std::unique_ptr<ctypes::Module> &module,
			const TypeWidths &typeWidths = {},
			const ctypes::CallConvention &callConvention = ctypes::CallConvention()) override;

	private:
		std::string loadJson(std::istream &stream) const;
		std::unique_ptr<rapidjson::Document> parseJson(char *buffer) const;
		void parseJsonIntoModule(
			const std::unique_ptr<rapidjson::Document> &root,
			std::unique_ptr<ctypes::Module> &module);
		void addTypesToMap(const rapidjson::Value &types);

		/// @name Parsing methods.
		/// @{
		void handleParsingFailure(const rapidjson::ParseResult &err) const;
		std::shared_ptr<ctypes::Function> getOrParseFunction(
			const std::string &name,
			const rapidjson::Value &jsonFunction
		);
		std::shared_ptr<ctypes::Function> parseFunction(
			const rapidjson::Value &function,
			const std::string &fName
		);
		ctypes::Function::Parameters parseParameters(
			const rapidjson::Value &jsonParams
		);
		ctypes::Parameter parseParameter(
			const rapidjson::Value &param
		);
		ctypes::FunctionType::VarArgness parseVarArgness(
			const rapidjson::Value &function
		) const;
		std::string parseCallConv(
			const rapidjson::Value &function
		) const;
		ctypes::Parameter::Annotations parseAnnotations(
			const std::string &annot
		) const;
		std::shared_ptr<ctypes::FunctionType> parseFunctionType(
			const rapidjson::Value &jsonFuncType
		);
		ctypes::FunctionType::Parameters parseFunctionTypeParameters(
			const rapidjson::Value &jsonParams
		);
		std::shared_ptr<ctypes::Type> getOrParseType(
			const std::string &typeKey
		);
		std::shared_ptr<ctypes::Type> parseType(
			const std::string &typeKey
		);
		std::shared_ptr<ctypes::Type> parseIntegralType(
			const rapidjson::Value &type
		);
		std::shared_ptr<ctypes::Type> parseFloatingPointType(
			const rapidjson::Value &type
		);
		std::shared_ptr<ctypes::Type> parseTypedefedType(
			const rapidjson::Value &jsonTypedef
		);
		std::shared_ptr<ctypes::Type> parseStruct(
			const rapidjson::Value &jsonStruct
		);
		std::shared_ptr<ctypes::Type> parseUnion(
			const rapidjson::Value &jsonUnion
		);
		ctypes::CompositeType::Members parseMembers(
			const rapidjson::Value &jsonMembers
		);
		std::shared_ptr<ctypes::PointerType> parsePointer(
			const rapidjson::Value &jsonPointer
		);
		std::shared_ptr<ctypes::ArrayType> parseArray(
			const rapidjson::Value &jsonArray
		);
		ctypes::ArrayType::Dimensions parseArrayDimensions(
			const rapidjson::Value &jsonDimensions
		) const;
		std::shared_ptr<ctypes::Type> parseEnum(
			const rapidjson::Value &jsonEnum
		);
		ctypes::EnumType::Values parseEnumItems(
			const rapidjson::Value &jsonEnumItems
		) const;
		std::shared_ptr<ctypes::Type> getOrParseNamedType(
			const rapidjson::Value &jsonType,
			const std::function<
				std::shared_ptr<ctypes::Type> (const std::string &typeName)
			> &parseType
		);
		unsigned getIntegralTypeBitWidth(const std::string &type) const;
		unsigned getBitWidthOrDefault(const std::string &typeName) const;
		/// @}

	private:
		using ParserContext = std::unordered_map<std::string, std::shared_ptr<ctypes::Type>>;
		using TypesMap = std::unordered_map<std::string, rapidjson::Value::ConstMemberIterator>;

	private:
		/// Context for the parser (to speedup the parsing).
		ParserContext parserContext;

		/// Map used to store pointers to JSON types (to speedup the parsing).
		TypesMap typesMap;
};

} // namespace ctypesparser

#endif
