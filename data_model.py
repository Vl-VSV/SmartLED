from pydantic import Field
from pydantic.main import BaseModel


class DataModel(BaseModel):
    mode: int = Field(ge=1, le=4, default=1)
    submode: int = Field(ge=1, le=9, default=1)
    settings_0: int = Field(ge=0, le=255, default=90)
    settings_1: int = Field(ge=0, le=255, default=255)
    volF_k: int = Field(ge=10, le=255, default=30)


data = DataModel()
