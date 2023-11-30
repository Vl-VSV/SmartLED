from fastapi import APIRouter, Query
from data_model import data, DataModel
import random

router = APIRouter()


# Control Functions
def get_mode_name():
    if data.mode == 1:
        if data.submode == 1:
            return "Белый свет"
        if data.submode == 2:
            return "Постоянный свет"
        if data.submode == 3:
            return "Плавная смена цвета"
    if data.mode == 2:
        if data.submode == 1:
            return "Радуга"
        if data.submode == 2:
            return "Конфетти"
        if data.submode == 3:
            return "Бегающая точка"
        if data.submode == 4:
            return "Огонь"
        if data.submode == 5:
            return "Лава"
        if data.submode == 6:
            return "Облака"
    if data.mode == 3:
        if data.submode == 1:
            return "Музыкальные огни из центра"
        if data.submode == 2:
            return "Музыкальные огни с краю"
        if data.submode == 3:
            return "Одноцветные музыкальные огни из центра"
        if data.submode == 4:
            return "Одноцветные музыкальные огни с краю"
    if data.mode == 4:
        if data.submode == 1:
            return "Музыкальный градиент"
        if data.submode == 2:
            return "Музыкальные полоски"
        if data.submode == 3:
            return "Музыкальные облака"
        if data.submode == 4:
            return "Музыкальная вечеринка"
        if data.submode == 5:
            return "Музыкальный океан"
        if data.submode == 6:
            return "Музыкальная радуга"
        if data.submode == 7:
            return "Музыкальная лава"
        if data.submode == 8:
            return "Музыкальный лес"
        if data.submode == 9:
            return "Музыкальная жара"


@router.get('/getData', response_model=DataModel)
def get_data():
    """
    Retrieves current LED status data.
    """
    return data


@router.get('/setModeAndSubmode')
def set_mode(new_mode: int = Query(ge=1, le=4, default=1), new_submode: int = Query(ge=1, le=9, default=1)):
    """
    Used to set a new LED mode and sub-mode.
    """
    if data.mode != 1 and new_mode == 1:
        data.settings_0 = 90
        data.settings_1 = 255
    elif data.mode != 2 and new_mode == 2:
        data.settings_1 = 255
    elif data.mode != 3 and new_mode == 3:
        data.settings_1 = 255
    elif data.mode != 5 and new_mode == 4:
        data.volF_k = 30
        data.settings_1 = 1

    data.mode = new_mode
    data.submode = new_submode
    return {'new_mode': data.mode, 'new_submode': data.submode, 'name': get_mode_name()}


@router.get('/setRandomMode')
def set_random_mode():
    """
    Used to set a random LED mode and sub-mode.
    """

    limits = [3, 6, 4, 9]
    data.mode = random.randint(1, 4)
    data.submode = random.randint(1, limits[data.mode - 1])

    return {'new_mode': data.mode, 'new_submode': data.submode, 'name': get_mode_name()}


@router.get('/setNextMode')
def set_next_mode():
    """
    Used to set a next LED mode.
    """

    limits = [3, 6, 4, 9]
    if data.submode < limits[data.mode - 1]:
        data.submode += 1
    else:
        if data.mode < 4:
            data.mode += 1
        else:
            data.mode = 1
        data.submode = 1

    return {'new_mode': data.mode, 'new_submode': data.submode, 'name': get_mode_name()}


@router.get('/setPreviousMode')
def set_previous_mode():
    """
    Used to set a previous LED mode.
    """

    limits = [3, 6, 4, 9]
    if data.submode > 1:
        data.submode -= 1
    else:
        if data.mode > 1:
            data.mode -= 1
        else:
            data.mode = 4
        data.submode = limits[data.mode - 1]

    return {'new_mode': data.mode, 'new_submode': data.submode, 'name': get_mode_name()}


@router.get('/whatMode')
def get_current_mode_name():
    return {'name': get_mode_name()}
