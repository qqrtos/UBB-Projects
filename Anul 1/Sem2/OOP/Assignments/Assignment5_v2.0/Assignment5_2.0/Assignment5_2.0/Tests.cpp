#include <cassert>
#include "Tests.h"
#include "SeniorService.h"
#include "DynamicVector.h"
#include <vector>
#include <fstream>
#include <stdio.h>
#include "AssistantService.h"

void Tests::runTests() {
	runDomainTests();
	runDynamicVectorTests();
	runAbstractRepositoryTests();
	runInMemoryRepositoryTests();
	runTextFileRepositoryTests();
	runSeniorServiceTests();
	runAssistantServiceTests();
}

void Tests::runDomainTests() {
	runMaterialTests();
	runSizeTests();
}

void Tests::runDynamicVectorTests() {
	DynamicVector_getCount__AnyVector__CorrectSize();
	DynamicVector_append__AnyElement__SizeChanged();
	DynamicVector_remove__ExistentElement__Success();
	DynamicVector_remove__InexistentElement__ReturnsError();
	DynamicVector_getElementAtIndex__AnyVector__CorrectIndex();
	DynamicVector_getElementAtIndex__AnyVector__IndexOutOfBound();
	DynamicVector_iterate__AnyVector__CorrectIteration();
}

void Tests::runAbstractRepositoryTests() {
	AbstractRepository_instantiate__AnyRepository__FunctionsPass();
}

void Tests::runInMemoryRepositoryTests() {
	InMemoryRepository_AddMaterial__ValidID__ElementAdded();
	InMemoryRepository_RemoveMaterial__ExistentElement__ElementRemoved();
	InMemoryRepository_RemoveMaterial__NonexistentElement__ReturnsError();
	InMemoryRepository_RemoveMaterial__InexistentElement__CountNotDecreased();
	InMemoryRepository_UpdateMaterial__InvalidID__ReturnsError();
	InMemoryRepository_UpdateMaterial__ValidID__ElementUpdated();
	InMemoryRepository_GetCount__AnyRepo__CorrectCount();
}

void Tests::runTextFileRepositoryTests() {
	TextFileRepository_ChangeFilePath__NonEmptyString__PathChanged();
	TextFileRepository_AddMaterial__MaterialAdded__RepositoryCountIncreased();
	TextFileRepository_GetRepoCount__NonEmptyRepository__CorrectCount();
	TextFileRepository_GetMaterialByID__MaterialInRepository__CorrectMaterialReturned();
	TextFileRepository_GetMaterialByID__MaterialNotInRepository__ThrowsException();
	TextFileRepository_UpdateMaterial__MaterialInRepository__MaterialUpdated();
	TextFileRepository_RemoveMaterial__MaterialInRepository__MaterialRemoved();
}

void Tests::runSeniorServiceTests() {
	SeniorService_AddMaterial__AnyMaterial__AddedSuccesfully();
	SeniorService_GetAllElements__AnyService__CorrectElements();
	SeniorService_GetElementByID__CorrectID__CorrectElement();
	SeniorService_GetElementByID__IncorrectID__ReturnsError();
	SeniorService_UpdateMaterial__CorrectID__MaterialUpdated();
	SeniorService_RemoveMaterial__CorrectID__MaterialRemoved();
	SeniorService_ChangeFilePath__NewFile__PathChanged();
}

void Tests::runAssistantServiceTests() {
	AssistantService_filter_CorrespondingMaterialsFound__ReturnedNonEmptyVector();
	AssistantService_filter_CorrespondingMaterialsNotFound__ReturnedEmptyVector();
	AssistantService_SaveMaterialForStudy__ValidMaterial__AddedToAssistantList();
	AssistantService_SaveMaterialForStudy__InvalidMaterial__AssistantListNotChanged();
	AssistantService_GetAssistantMaterialsList();
}

void Tests::runMaterialTests() {
	Material_Create__InvalidID__ExceptionThrown();
	Material_Create__NegativeNumberMicrofragments__ExceptionThrown();
	Material_Create__InvalidDigitizedScan__ExceptionThrown();
	Material_AssignOperator__ValidInput__Success();
	Material_WriteToFile__ValidFile__Success();
	Material_ReadFromFile__ValidFileInput__Success();
}

void Tests::runSizeTests() {
	Size_CreateSize__InvalidInput__ThrowsException();
	Size_EqualsOperator__Equal__ReturnsTrue();
	Size_EqualsOperator__NotEqual__ReturnsFalse();
}

void Tests::Material_Create__InvalidID__ExceptionThrown() {
	try {
		Material emptyIDmaterial{ "a",Size{1,1,1},4,4,"asca" };
		emptyIDmaterial.setID("");
		assert(false);
	}
	catch (...) {
		assert(true);
	}
}

void Tests::Material_Create__InvalidDigitizedScan__ExceptionThrown() {
	try {
		Material emptyDigitizedScan{ "1",Size{10,10,10},1,1,"av" };
		emptyDigitizedScan.setDigitizedScan("");
		assert(false);
	}
	catch (...) {
		assert(true);
	}
}

void Tests::Material_Create__NegativeNumberMicrofragments__ExceptionThrown() {
	try {
		Material negativeNrMicrofragments{ "1",Size{10,10,10},3,1,"asc" };
		negativeNrMicrofragments.setQuantityOfMicrofragments(-5);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
}

void Tests::Material_WriteToFile__ValidFile__Success() {
	std::ofstream fout("testDomain.txt");
	Material write{ "1",Size{1,1,1},2,2,"asc" };
	fout << write.toString() << "\n" << write << "\n";
	fout.close();
}

void Tests::Material_AssignOperator__ValidInput__Success() {
	Material firstMaterial{ "1",Size{1,1,1},2,2,"a" };
	Material secondMaterial{ "2",Size{2,2,2},3,3,"b" };
	firstMaterial = secondMaterial;
	assert(firstMaterial.getID() == "2");
}

void Tests::Size_CreateSize__InvalidInput__ThrowsException() {
	try {
		Size invalid{ -1,1,1 };
		assert(false);
	}
	catch (...) {
		assert(true);
	}
}

void Tests::Size_EqualsOperator__Equal__ReturnsTrue() {
	Size s1{ 1,1,1 };
	Size s2{ 1,1,1 };
	assert(s1 == s2);
}

void Tests::Size_EqualsOperator__NotEqual__ReturnsFalse() {
	Size s1{ 1,1,1 };
	Size s2{ 1,1,2 };
	assert(!(s1 == s2));
}

void Tests::Material_ReadFromFile__ValidFileInput__Success() {
	Material m{};
	std::ifstream fileInput("testDomain.txt");
	fileInput >> m;
	fileInput.close();
}

void Tests::DynamicVector_append__AnyElement__SizeChanged() {
	DynamicVector<float> vector{};
	vector.append(3.5);
	vector.append(1.5);
	assert(vector.getCount() == 2);
}

void Tests::DynamicVector_remove__ExistentElement__Success() {
	DynamicVector<int> vector{};
	vector.append(3);
	vector.append(5);
	vector.append(4);
	vector.append(1);
	try {
		vector.remove(5);
		return;
	}
	catch (...) {
		assert(false);
	}
}

void Tests::DynamicVector_remove__InexistentElement__ReturnsError() {
	DynamicVector<int> vector{};
	vector.append(5);
	try {
		vector.remove(1);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
}

void Tests::DynamicVector_getCount__AnyVector__CorrectSize() {
	DynamicVector<int> vector{};
	vector.append(3);
	vector.append(5);
	vector.remove(5);
	assert(vector.getCount() == 1);
}

void Tests::DynamicVector_getElementAtIndex__AnyVector__CorrectIndex() {
	DynamicVector<int> vector{};
	vector.append(3);
	vector.append(5);
	assert(vector[1] == 5);
}

void Tests::DynamicVector_getElementAtIndex__AnyVector__IndexOutOfBound() {
	DynamicVector<int> vector{};
	vector.append(3);
	vector.append(5);
	try {
		assert(vector[2] == 5);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
}

void Tests::DynamicVector_iterate__AnyVector__CorrectIteration() {
	DynamicVector<int> vector{};
	vector.append(3);
	vector.append(5);
	vector.append(3);
	vector.append(5);

	int i = 0;

	for (const int element : vector) {
		if (i % 2 == 0) {
			assert(element == 3);
		}
		else {
			assert(element == 5);
		}
		++i;
	}
}

void Tests::AbstractRepository_instantiate__AnyRepository__FunctionsPass() {
	Repository* repository = new InMemoryRepository();
	std::vector<Material> v;
	Material m{};
	delete repository;
	repository = new TextFileRepository("");
	delete repository;
}

void Tests::InMemoryRepository_GetCount__AnyRepo__CorrectCount() {
	InMemoryRepository repository{};
	Material newMaterial{ "ID",Size{1,1,1}, 2,1,"digit" };
	repository.addMaterial(newMaterial);
	newMaterial.setID("3ID");
	repository.addMaterial(newMaterial);
	assert(repository.getRepositoryCount() == 2);
}

void Tests::InMemoryRepository_AddMaterial__ValidID__ElementAdded() {
	InMemoryRepository repository{};
	Material newMaterial{ "IIID", Size{5,5,5}, 2, 1, "SN" };
	repository.addMaterial(newMaterial);
	std::vector<Material> vector = repository.getAllMaterials();
	Material checkMaterial = Material{ "IIID",Size{1,1,1},2,1,"SN" };
	assert(vector[0] == checkMaterial);
}

void Tests::InMemoryRepository_RemoveMaterial__ExistentElement__ElementRemoved() {
	InMemoryRepository repository{};
	Material newMaterial{ "ID", Size{3,3,3}, 4,5,"vasvrrr" };
	repository.addMaterial(newMaterial);
	repository.removeMaterial(newMaterial);
	assert(repository.getRepositoryCount() == 0);
}

void Tests::InMemoryRepository_RemoveMaterial__NonexistentElement__ReturnsError() {
	InMemoryRepository repository{};
	Material material{ "ID", Size{3,3,3}, 4,5,"vasvrrr" };
	Material inexistentMaterial{ "alt", Size{3,3,3}, 4,5,"vasvrrr" };
	repository.addMaterial(material);
	try {
		repository.removeMaterial(inexistentMaterial);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
}

void Tests::InMemoryRepository_RemoveMaterial__InexistentElement__CountNotDecreased() {
	InMemoryRepository repository{};
	Material material{ "ID", Size{3,3,3}, 4,5,"vasvrrr" };
	Material inexistentMaterial{ "ID2", Size{3,3,3}, 4,5,"va" };
	repository.addMaterial(material);
	try { repository.removeMaterial(inexistentMaterial); }
	catch (...) {};
	assert(repository.getRepositoryCount() == 1);
}

void Tests::InMemoryRepository_UpdateMaterial__InvalidID__ReturnsError() {
	InMemoryRepository repository{};
	Material material{ "ID", Size{3,3,3}, 4,5,"vasvrrr" };
	Material updatedMaterial{ "alt", Size{3,3,3}, 4,5,"vrrr" };
	repository.addMaterial(material);
	try {
		repository.updateMaterial(updatedMaterial.getID(), updatedMaterial);
		assert(false);
	}
	catch (...) {
		assert(true);
	}
}

void Tests::InMemoryRepository_UpdateMaterial__ValidID__ElementUpdated() {
	InMemoryRepository repository{};
	Material material{ "ID", Size{3,3,3}, 4,5,"vasvrrr" };
	Material updatedMaterial{ "ID", Size{3,3,3}, 1,1,"vrrr" };
	repository.addMaterial(material);
	repository.updateMaterial(updatedMaterial.getID(), updatedMaterial);
	std::vector<Material> materials = repository.getAllMaterials();
	assert(materials[0].getRadioactivityLevel() == 1 && materials[0].getQuantityOfMicrofragments() == 1);
}

void Tests::TextFileRepository_ChangeFilePath__NonEmptyString__PathChanged() {
	TextFileRepository repository{ "testFileRepo.txt" };
	repository.changeCurrentFile("test2.txt");
	assert(repository.getFilePath() == "test2.txt");
	remove("testFileRepo.txt");
}

void Tests::TextFileRepository_AddMaterial__MaterialAdded__RepositoryCountIncreased() {
	TextFileRepository repository{ "testFileRepo.txt" };
	repository.addMaterial(Material{ "1",Size{10,10,10},1,1,"adc" });

	std::ifstream inputStream("testFileRepo.txt", std::ios::app | std::ios::out);

	assert(std::count(std::istreambuf_iterator<char>(inputStream),
		std::istreambuf_iterator<char>(), '\n') == 1);

	inputStream.close();
	remove("testFileRepo.txt");
}

void Tests::TextFileRepository_GetRepoCount__NonEmptyRepository__CorrectCount() {
	TextFileRepository repository{ "testFileRepo.txt" };
	repository.addMaterial(Material{ "1", Size{ 1,1,1 }, 1, 1, "aaa" });
	repository.addMaterial(Material{ "2", Size{ 1,1,1 }, 1, 1, "bbb" });
	assert(repository.getRepositoryCount() == 2);
	remove("testFileRepo.txt");
}

void Tests::TextFileRepository_GetMaterialByID__MaterialInRepository__CorrectMaterialReturned() {
	TextFileRepository repository{ "testFileRepo.txt" };
	repository.addMaterial(Material{ "1",Size{1,1,1},1,1,"adc" });
	repository.addMaterial(Material{ "3",Size{1,1,1},3,3,"cadcb" });
	assert(repository.getMaterialByID("1").getID() == "1");
	remove("testFileRepo.txt");
}

void Tests::TextFileRepository_GetMaterialByID__MaterialNotInRepository__ThrowsException() {
	TextFileRepository repository{ "testFileRepo.txt" };
	repository.addMaterial(Material{ "1",Size{1,1,1},1,1,"adc" });
	repository.addMaterial(Material{ "3",Size{1,1,1},3,3,"cadcb" });
	try {
		Material found = repository.getMaterialByID("2");
		assert(false);
	}
	catch (...) {
		assert(true);
	}
	remove("testFileRepo.txt");
}

void Tests::TextFileRepository_UpdateMaterial__MaterialInRepository__MaterialUpdated() {
	TextFileRepository repository{ "testFileRepo.txt" };
	repository.addMaterial(Material{ "1",Size{1,1,1},1,1,"adc" });
	repository.addMaterial(Material{ "3",Size{1,1,1},3,3,"cadcb" });
	repository.updateMaterial("1", Material{ "1",Size{10,10,10},10,10,"adc" });
	Material updated = repository.getMaterialByID("1");
	assert(updated.getRadioactivityLevel() == 10 and updated.getQuantityOfMicrofragments() == 10);
	remove("testFileRepo.txt");
}

void Tests::TextFileRepository_RemoveMaterial__MaterialInRepository__MaterialRemoved() {
	TextFileRepository repository{ "testFileRepo.txt" };
	repository.addMaterial(Material{ "1",Size{1,1,1},1,1,"adc" });
	repository.addMaterial(Material{ "3",Size{1,1,1},3,3,"cadcb" });
	repository.removeMaterial(Material{ "1",Size{1,1,1},1,1,"adc" });
	assert(repository.getRepositoryCount() == 1);
	remove("testFileRepo.txt");
}

void Tests::SeniorService_AddMaterial__AnyMaterial__AddedSuccesfully() {
	TextFileRepository repository{ "testService.txt" };
	SeniorService service{ repository };
	service.addMaterial("1", Size{ 1,1,1 }, 1, 1, "aaa");
	assert(service.getAllMaterials().size() == 1);
	remove("testService.txt");
}

void Tests::SeniorService_GetAllElements__AnyService__CorrectElements() {
	TextFileRepository repository{"testService.txt"};
	SeniorService service{ repository };
	service.addMaterial("Id", Size{ 1,1,1 }, 3, 3, "asv");
	service.addMaterial("di", Size{ 2,2,2 }, 5, 5, "fred");
	std::vector<Material> vector = service.getAllMaterials();
	assert(vector[0].getID() == "Id" && vector[1].getID() == "di");
	remove("testService.txt");
}

void Tests::SeniorService_GetElementByID__CorrectID__CorrectElement() {
	TextFileRepository repository{ "testService.txt" };
	SeniorService service{ repository };
	service.addMaterial("ID", Size{ 1,1,1 }, 3, 3, "RE");
	Material m = service.getElementByID("ID");
	assert(m.getDigitizedScan() == "RE");
	remove("testService.txt");
}

void Tests::SeniorService_GetElementByID__IncorrectID__ReturnsError() {
	TextFileRepository repository{ "testService.txt" };
	SeniorService service{ repository };
	service.addMaterial("ID", Size{ 1,1,1 }, 3, 4, "Abda");
	try {
		Material found = service.getElementByID("fred");
		assert(false);
	}
	catch (...) {
		assert(true);
	}
	remove("testService.txt");
}

void Tests::SeniorService_UpdateMaterial__CorrectID__MaterialUpdated() {
	TextFileRepository repository{ "testService.txt" };
	SeniorService service{ repository };
	service.addMaterial("1", Size{ 1,1,1 }, 1, 1, "aaa");
	service.updateMaterial("1", Size{ 10,10,10 }, 10, 10, "aaa");
	assert(service.getElementByID("1").getRadioactivityLevel() == 10);
	remove("testService.txt");
}

void Tests::SeniorService_RemoveMaterial__CorrectID__MaterialRemoved() {
	TextFileRepository repository{ "testService.txt" };
	SeniorService service{ repository };
	service.addMaterial("1", Size{ 1,1,1 }, 1, 1, "aaa");
	service.addMaterial("2", Size{ 2,2,2 }, 2, 2, "bbb");
	service.addMaterial("3", Size{ 3,3,3 }, 3, 3, "ccc");
	service.removeMaterial("1");
	assert(service.getAllMaterials().size() == 2);
	remove("testService.txt");
}

void Tests::SeniorService_ChangeFilePath__NewFile__PathChanged() {
	TextFileRepository repository{ "testService.txt" };
	SeniorService service{ repository };
	service.changeFileLocation("testDomain.txt");
	assert(service.getFilePath() == "testDomain.txt");
}

void Tests::AssistantService_SaveMaterialForStudy__ValidMaterial__AddedToAssistantList() {
	InMemoryRepository seniorRepository{};
	InMemoryRepository assistantRepository{};
	seniorRepository.addMaterial(Material{ "1",Size{1,1,1},1,1,"aaa" });
	seniorRepository.addMaterial(Material{ "2",Size{2,2,2},2,2,"bbb" });
	seniorRepository.addMaterial(Material{ "3",Size{3,3,3},3,3,"ccc" });
	AssistantService service{ seniorRepository, assistantRepository };
	service.saveMaterialForStudy("1");
	std::vector<Material> savedMaterials = service.getAssistantMaterialsList();
	assert(savedMaterials[0].getID() == "1" and savedMaterials[0].getRadioactivityLevel() == 1);
}

void Tests::AssistantService_SaveMaterialForStudy__InvalidMaterial__AssistantListNotChanged() {
	InMemoryRepository seniorRepository{};
	InMemoryRepository assistantRepository{};
	seniorRepository.addMaterial(Material{ "1",Size{1,1,1},1,1,"aaa" });
	seniorRepository.addMaterial(Material{ "2",Size{2,2,2},2,2,"bbb" });
	AssistantService service{ seniorRepository, assistantRepository };
	service.saveMaterialForStudy("3");
	std::vector<Material> assistantList = service.getAssistantMaterialsList();
	assert(assistantList.size() == 0);
}

void Tests::AssistantService_GetAssistantMaterialsList() {
	InMemoryRepository seniorRepository{};
	InMemoryRepository assistantRepository{};
	seniorRepository.addMaterial(Material{ "1",Size{1,1,1},1,1,"aaa" });
	seniorRepository.addMaterial(Material{ "3",Size{3,3,3},3,3,"ccc" });
	AssistantService service{ seniorRepository, assistantRepository };
	service.saveMaterialForStudy("1");
	service.saveMaterialForStudy("3");
	std::vector<Material> assistantList = service.getAssistantMaterialsList();
	assert(assistantList.size() == 2 and assistantList[0].getID() == "1" and assistantList[1].getID() == "3");
}

void Tests::AssistantService_filter_CorrespondingMaterialsFound__ReturnedNonEmptyVector() {
	InMemoryRepository seniorRepository{};
	InMemoryRepository assistantRepository{};
	seniorRepository.addMaterial(Material{ "1",Size{1,1,1},1,1,"aaa" });
	seniorRepository.addMaterial(Material{ "3",Size{3,3,3},3,3,"ccc" });
	AssistantService service{ seniorRepository, assistantRepository };
	service.saveMaterialForStudy("1");
	service.saveMaterialForStudy("3");
	std::vector<Material> filteredMaterials = service.filterBySizeAndMicrofragments(Size{ 1,1,1 }, 0);
	assert(filteredMaterials[0].getID() == "1" and filteredMaterials[0].getRadioactivityLevel() == 1);
}

void Tests::AssistantService_filter_CorrespondingMaterialsNotFound__ReturnedEmptyVector() {
	InMemoryRepository seniorRepository{};
	InMemoryRepository assistantRepository{};
	seniorRepository.addMaterial(Material{ "1",Size{1,1,1},1,1,"aaa" });
	seniorRepository.addMaterial(Material{ "3",Size{3,3,3},3,3,"ccc" });
	AssistantService service{ seniorRepository, assistantRepository };
	service.saveMaterialForStudy("1");
	service.saveMaterialForStudy("3");
	std::vector<Material> filteredMaterials = service.filterBySizeAndMicrofragments(Size{ 1,1,1 }, 2);
	assert(filteredMaterials.empty());
}