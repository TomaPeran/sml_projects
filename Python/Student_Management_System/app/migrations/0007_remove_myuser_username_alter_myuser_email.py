# Generated by Django 5.0.6 on 2024-05-24 00:55

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('app', '0006_alter_role_role'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='myuser',
            name='username',
        ),
        migrations.AlterField(
            model_name='myuser',
            name='email',
            field=models.EmailField(max_length=254, unique=True, verbose_name='email address'),
        ),
    ]