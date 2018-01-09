//
// Created by Fady on 1/8/2018.
//

#include "library2.h"
#include "Colosseum.h"

void* init(int n, int* trainingGroupsIDs) {
    if(n < 2 || trainingGroupsIDs == NULL)
        return NULL;

    Colosseum* DS;

    try{
        DS = new Colosseum(n, trainingGroupsIDs);
    }
    catch(Fail& exc) {
        return NULL;
    }

    return (void*)DS;
}


StatusType addGladiator(void *DS, int gladiatorID, int score, int trainingGroup){
    if(DS == NULL)
        return INVALID_INPUT;
    try{
        ((Colosseum*)DS)->addGladiator(gladiatorID , score , trainingGroup);
    }
    catch(Invalid_Input& exc){
        return INVALID_INPUT;
    }
    catch (Fail& exc){
        return FAILURE;
    }
    catch (std::bad_alloc& exc){
        return ALLOCATION_ERROR;
    }

    return SUCCESS;

}

StatusType trainingGroupFight(void *DS, int trainingGroup1, int trainingGroup2, int k1, int k2) {
    if(DS == NULL)
        return INVALID_INPUT;
    try{
        ((Colosseum*)DS)->trainingGroupFight(trainingGroup1 , trainingGroup2 , k1, k2);
    }
    catch(Invalid_Input& exc){
        return INVALID_INPUT;
    }
    catch (Fail& exc){
        return FAILURE;
    }
    catch (std::bad_alloc& exc){
        return ALLOCATION_ERROR;
    }

    return SUCCESS;

}

void quit(void** DS) {
    if (DS != NULL) {
        delete (*(Colosseum **) DS);
        *DS = NULL;
    }
}


StatusType   getMinTrainingGroup(void* DS, int* trainingGroup) {
    if(DS == NULL)
        return INVALID_INPUT;
    try{
        ((Colosseum*)DS)-> getMinTrainingGroup(trainingGroup);
    }
    catch(Invalid_Input& exc){
        return INVALID_INPUT;
    }
    catch (Fail& exc){
        return FAILURE;
    }
    catch (std::bad_alloc& exc){
        return ALLOCATION_ERROR;
    }

    return SUCCESS;
}


StatusType addTrainingGroup(void *DS, int trainingGroupID){
    if(DS == NULL)
        return INVALID_INPUT;
    try{
        ((Colosseum*)DS)->addTrainingGroup(trainingGroupID);
    }
    catch(Invalid_Input& exc){
        return INVALID_INPUT;
    }
    catch (Fail& exc){
        return FAILURE;
    }
    catch (std::bad_alloc& exc){
        return ALLOCATION_ERROR;
    }

    return SUCCESS;
}





