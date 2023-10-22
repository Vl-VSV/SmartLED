from data_model import data
from fastapi import HTTPException


def change_temperature(operand: str):
    if data.mode == 1 and data.submode == 1:
        if operand == "+":
            data.settings_0 = min(180, data.settings_0 + 15)
        elif operand == "-":
            data.settings_0 = max(0, data.settings_0 - 15)
        elif operand == "max":
            data.settings_0 = 180
        elif operand == "min":
            data.settings_0 = 0
        return {"new_temperature": data.settings_0}
    else:
        raise HTTPException(status_code=400, detail="Нельзя изменить оттенок цвета в текущем режиме")


def change_brightness(operand: str):
    if data.mode == 1 and data.submode == 1:
        if operand == "+":
            data.settings_1 = min(255, data.settings_1 + 16)
        elif operand == "-":
            data.settings_1 = max(0, data.settings_1 - 16)
        elif operand == "max":
            data.settings_1 = 255
        elif operand == "min":
            data.settings_1 = 0
        return {"new_brightness": data.settings_1}
    else:
        raise HTTPException(status_code=400, detail="Нельзя изменить яркость в текущем режиме")


def change_animation_smooth(operand: str):
    if data.mode == 4:
        if operand == "+":
            data.volF_k = min(31, data.volF_k + 1)
        elif operand == "-":
            data.volF_k = max(10, data.volF_k - 1)
        elif operand == "max":
            data.volF_k = 31
        elif operand == "min":
            data.volF_k = 10
        return {"new_animation_smooth": data.volF_k}
    else:
        raise HTTPException(status_code=400, detail="Нельзя изменить плавность анимации в текущем режиме")


def change_rainbow_step(operand: str):
    if data.mode == 2 and data.submode == 1:
        if operand == "+":
            data.settings_1 = min(255, data.settings_1 + 1)
        elif operand == "-":
            data.settings_1 = max(1, data.settings_1 - 1)
        elif operand == "max":
            data.settings_1 = 255
        elif operand == "min":
            data.settings_1 = 1
        return {"new_rainbow_step": data.settings_1}
    else:
        raise HTTPException(status_code=400, detail="Нельзя изменить шаг радуги в текущем режиме")


def change_saturation(operand: str):
    if (data.mode == 1 and (data.submode == 2 or data.submode == 3)) or (
            data.mode == 2 and (data.submode == 2 or data.submode == 3)) or (data.mode == 3):
        if operand == "+":
            data.settings_1 = min(255, data.settings_1 + 16)
        elif operand == "-":
            data.settings_1 = max(0, data.settings_1 - 16)
        elif operand == "max":
            data.settings_1 = 255
        elif operand == "min":
            data.settings_1 = 0
        return {"new_saturation": data.settings_1}
    else:
        raise HTTPException(status_code=400, detail="Нельзя изменить насыщенность в текущем режиме")


def change_speed(operand: str) -> int:
    if data.mode == 1 and data.submode == 3 or data.mode == 2:
        if operand == "+":
            data.settings_0 = min(255, data.settings_0 + 10)
        elif operand == "-":
            data.settings_0 = max(1, data.settings_0 - 10)
        elif operand == "max":
            data.settings_0 = 255
        elif operand == "min":
            data.settings_0 = 1
        return {"new_speed": data.settings_0}

    elif data.mode == 4 and 5 <= data.submode <= 9:
        if operand == "+":
            data.settings_1 = min(20, data.settings_1 + 1)
        elif operand == "-":
            data.settings_1 = max(1, data.settings_1 - 1)
        elif operand == "max":
            data.settings_1 = 20
        elif operand == "min":
            data.settings_1 = 1
        return {"new_speed": data.settings_1}

    else:
        raise HTTPException(status_code=400, detail="Нельзя изменить скорость в текущем режиме")
