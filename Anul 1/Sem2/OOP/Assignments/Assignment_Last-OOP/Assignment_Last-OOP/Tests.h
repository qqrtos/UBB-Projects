#pragma once

class Tests {
public:
	void runTests();

private:
	//Group tests by class.
	void runDomainTests();
	void runDynamicVectorTests();
	void runAbstractRepositoryTests();
	void runInMemoryRepositoryTests();
	void runTextFileRepositoryTests();
	void runSeniorServiceTests();
	void runAssistantServiceTests();

	//Domain tests.
	void runMaterialTests();
	void runSizeTests();

	//Material tests.
	void Material_Create__InvalidID__ExceptionThrown();
	void Material_Create__InvalidDigitizedScan__ExceptionThrown();
	void Material_Create__NegativeNumberMicrofragments__ExceptionThrown();
	void Material_ReadFromFile__ValidFileInput__Success();
	void Material_WriteToFile__ValidFile__Success();
	void Material_AssignOperator__ValidInput__Success();

	//Size tests.
	void Size_CreateSize__InvalidInput__ThrowsException();
	void Size_EqualsOperator__Equal__ReturnsTrue();
	void Size_EqualsOperator__NotEqual__ReturnsFalse();

	//Dynamic vector tests.
	void DynamicVector_append__AnyElement__SizeChanged();
	void DynamicVector_remove__ExistentElement__Success();
	void DynamicVector_remove__InexistentElement__ReturnsError();
	void DynamicVector_getCount__AnyVector__CorrectSize();
	void DynamicVector_getElementAtIndex__AnyVector__CorrectIndex();
	void DynamicVector_getElementAtIndex__AnyVector__IndexOutOfBound();
	void DynamicVector_iterate__AnyVector__CorrectIteration();

	//Abstract Repository class test.
	void AbstractRepository_instantiate__AnyRepository__FunctionsPass();

	//In memory repository tests.
	void InMemoryRepository_GetCount__AnyRepo__CorrectCount();
	void InMemoryRepository_AddMaterial__ValidID__ElementAdded();
	void InMemoryRepository_RemoveMaterial__ExistentElement__ElementRemoved();
	void InMemoryRepository_RemoveMaterial__NonexistentElement__ReturnsError();
	void InMemoryRepository_RemoveMaterial__InexistentElement__CountNotDecreased();
	void InMemoryRepository_UpdateMaterial__InvalidID__ReturnsError();
	void InMemoryRepository_UpdateMaterial__ValidID__ElementUpdated();

	//Text file repository tests.
	void TextFileRepository_ChangeFilePath__NonEmptyString__PathChanged();
	void TextFileRepository_AddMaterial__MaterialAdded__RepositoryCountIncreased();
	void TextFileRepository_GetRepoCount__NonEmptyRepository__CorrectCount();
	void TextFileRepository_GetMaterialByID__MaterialInRepository__CorrectMaterialReturned();
	void TextFileRepository_GetMaterialByID__MaterialNotInRepository__ThrowsException();
	void TextFileRepository_UpdateMaterial__MaterialInRepository__MaterialUpdated();
	void TextFileRepository_RemoveMaterial__MaterialInRepository__MaterialRemoved();

	//Senior service tests.
	void SeniorService_AddMaterial__AnyMaterial__AddedSuccesfully();
	void SeniorService_GetAllElements__AnyService__CorrectElements();
	void SeniorService_GetElementByID__CorrectID__CorrectElement();
	void SeniorService_GetElementByID__IncorrectID__ReturnsError();
	void SeniorService_UpdateMaterial__CorrectID__MaterialUpdated();
	void SeniorService_RemoveMaterial__CorrectID__MaterialRemoved();
	void SeniorService_ChangeFilePath__NewFile__PathChanged();

	//Assistant service tests.
	void AssistantService_SaveMaterialForStudy__ValidMaterial__AddedToAssistantList();
	void AssistantService_SaveMaterialForStudy__InvalidMaterial__AssistantListNotChanged();
	void AssistantService_GetAssistantMaterialsList();
	void AssistantService_filter_CorrespondingMaterialsFound__ReturnedNonEmptyVector();
	void AssistantService_filter_CorrespondingMaterialsNotFound__ReturnedEmptyVector();
};