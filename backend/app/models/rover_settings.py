
from datetime import datetime, timezone

from sqlalchemy import DateTime, Integer
from sqlalchemy.orm import Mapped, mapped_column

from app.database.base import Base


class RoverSettings(Base):
    """Database model for persistent rover settings."""

    __tablename__ = "rover_settings"

    id: Mapped[int] = mapped_column(
        Integer,
        primary_key=True,
    )

    speed_limit: Mapped[int] = mapped_column(
        Integer,
        default=100,
    )

    created_at: Mapped[datetime] = mapped_column(
        DateTime(timezone=True),
        default=lambda: datetime.now(timezone.utc),
    )

    updated_at: Mapped[datetime] = mapped_column(
        DateTime(timezone=True),
        default=lambda: datetime.now(timezone.utc),
    )
